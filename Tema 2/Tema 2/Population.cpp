#include "Population.h"

Population::Population(Evaluator* evaluator, unsigned int populationSize, unsigned int eliteSize, bool decreaseGeneticDiversity) :
	evaluator(evaluator), 
	populationSize(populationSize), 
	eliteSize(eliteSize),
	generation(0), 
	totalFitness(0),
	minValue(0),
	maxValue(0),
	decreaseGeneticDiversity(decreaseGeneticDiversity)
{
	individuals.reserve(populationSize);
	eliteIndividuals.reserve(eliteSize);

	for (unsigned int i = 0; i < populationSize; i++)
	{
		Chromosome chromosome(&(evaluator->dimesnions), &integerRandomGenerator);
		ChromosomeStats chromosomeStats;
		bitstringRandomGenerator.Random((Bitstring*)(&chromosome));
		
		Individual individual(chromosome , chromosomeStats);

		individuals.push_back(individual);
	}
}

void Population::Evolve()
{
	VALIDATE_RET(populationSize == individuals.size(), "Population size is not the same as the number of individuals");

	CalculateMinMax();
	FortuneWheelEval();
	EnsureElitism();
	SelectNewIndividuals();
	MutateIndividuals();
	CrossOverIndividuals();

	generation++;
}

long double Population::GetBest()
{
	CalculateMinMax();

	return minValue;
}

long double Population::GetFitness(Individual& individual)
{
	return ( maxValue - (evaluator->Evaluate((Bitstring*)(&(individual.first)))) ) / (maxValue - minValue);
}

void Population::CalculateMinMax()
{
	minValue = maxValue = evaluator->Evaluate((Bitstring*)(&(individuals[0].first)));

	double result = 0;

	for (unsigned int i = 0; i < populationSize; i++)
	{
		result = evaluator->Evaluate((Bitstring*)(&(individuals[i].first)));

		if (result > maxValue)
		{
			maxValue = result;
		}
		if (result < minValue)
		{
			minValue = result;
		}
	}

	for (unsigned int i = 0; i < eliteIndividuals.size(); i++)
	{
		result = evaluator->Evaluate((Bitstring*)(&(eliteIndividuals[i].first)));

		if (result > maxValue)
		{
			maxValue = result;
		}
		if (result < minValue)
		{
			minValue = result;
		}
	}
}

void Population::FortuneWheelEval()
{
	//Maybe we should also evaluate the elite

	totalFitness = 0;

	for (unsigned int i = 0; i < populationSize; i++)
	{
		individuals[i].second.eval = GetFitness(individuals[i]);
		totalFitness += individuals[i].second.eval;
	}

	individuals[0].second.individualProb = individuals[0].second.eval / totalFitness;
	individuals[0].second.cumulatedProb = 0;

	for (unsigned int i = 1; i < populationSize; i++)
	{
		individuals[i].second.individualProb = individuals[i].second.eval / totalFitness;
		individuals[i].second.cumulatedProb = individuals[i - 1].second.cumulatedProb + individuals[i - 1].second.individualProb;
	}
}

void Population::SelectNewIndividuals()
{
	std::vector<Individual> selectedIndividuals;
	selectedIndividuals.reserve(populationSize);

	long double r = 0;

	for (unsigned int i = 0; i < populationSize; i++)
	{
		r = realRandomGenerator.RandomBetween(0, 1);

		for (unsigned int j = 0; j < populationSize - 1; j++)
		{
			if (individuals[j].second.cumulatedProb < r && r <= individuals[j + 1].second.cumulatedProb)
			{
				selectedIndividuals.push_back(individuals[j]);
				break;
			}
		}

		if (individuals[populationSize - 1].second.cumulatedProb < r)
		{
			selectedIndividuals.push_back(individuals[populationSize - 1]);
		}
	}

	this->individuals = selectedIndividuals;
}

void Population::EnsureElitism()
{
	unsigned int bestEvalIndex = 0;
	unsigned int worstEvalIndex = 0;

	//Calculate fitness for the elite

	for (unsigned int i = 0; i < eliteIndividuals.size(); i++)
	{
		eliteIndividuals[i].second.eval = GetFitness(eliteIndividuals[i]);
	}

	//Clear elite status

	for (unsigned int i = 0; i < populationSize; i++)
	{
		individuals[i].second.isMemberOfTheElite = false;
	}

	for (unsigned int i = 0; i < eliteSize; i++)
	{
		unsigned int j = 0;

		//Initialize best and worst with and individual not already in the elite

		for (j; j < populationSize; j++)
		{
			VALIDATE_CONT(individuals[j].second.isMemberOfTheElite == false);
			bestEvalIndex = worstEvalIndex = j;
			break;
		}

		//Find best and worst individual

		for (j; j < populationSize; j++)
		{
			VALIDATE_CONT(individuals[j].second.isMemberOfTheElite == false);

			if (individuals[j].second.eval > individuals[bestEvalIndex].second.eval)
			{
				bestEvalIndex = j;
			}
			if (individuals[j].second.eval < individuals[worstEvalIndex].second.eval)
			{
				worstEvalIndex = j;
			}
		}

		//Treat case where this the first time elitism is ensured

		if (i + 1 > eliteIndividuals.size())
		{
			eliteIndividuals.push_back(individuals[bestEvalIndex]);
			individuals[bestEvalIndex].second.isMemberOfTheElite = true;
			continue;
		}

		//If not, establish the elite

		if (individuals[bestEvalIndex].second.eval > eliteIndividuals[i].second.eval)
		{
			eliteIndividuals.insert(eliteIndividuals.begin() + i, individuals[bestEvalIndex]);
			individuals[bestEvalIndex].second.isMemberOfTheElite = true;
			eliteIndividuals.pop_back();
		}
		else
		{
			totalFitness - individuals[worstEvalIndex].second.eval;

			individuals[worstEvalIndex] = eliteIndividuals[i];
			individuals[worstEvalIndex].second.isMemberOfTheElite = true;

			totalFitness + individuals[worstEvalIndex].second.eval;
			
		}
	}

	//Recalculate cumulated probability

	individuals[0].second.individualProb = individuals[0].second.eval / totalFitness;
	individuals[0].second.cumulatedProb = 0;

	for (unsigned int i = 1; i < populationSize; i++)
	{
		individuals[i].second.individualProb = individuals[i].second.eval / totalFitness;
		individuals[i].second.cumulatedProb = individuals[i - 1].second.cumulatedProb + individuals[i - 1].second.individualProb;
	}
}

void Population::MutateIndividuals()
{
	for (auto& it : individuals)
	{
		it.first.Mutate();
		it.first.Mutate();
		it.first.Mutate();
		it.first.Mutate();
	}
}

void Population::CrossOverIndividuals()
{
	unsigned int indexA = 0;
	unsigned int indexB = 0;

	unsigned int geneticDiversityReductionFactor = 1;

	if (decreaseGeneticDiversity)
	{
		geneticDiversityReductionFactor = log2(integerRandomGenerator.RandomBetween(1, generation + 1)) + 1;
	}

	for (unsigned int i = 0; i < populationSize / (2 * geneticDiversityReductionFactor); i++)
	{
		indexA = integerRandomGenerator.RandomBetween(0, populationSize / 2 - 1);
		indexB = integerRandomGenerator.RandomBetween(populationSize / 2, populationSize - 1);
	
		CrossOver(individuals[indexA].first, individuals[indexB].first);
	}
}