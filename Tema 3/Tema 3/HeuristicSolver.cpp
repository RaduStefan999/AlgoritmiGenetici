#include "HeuristicSolver.h"

HeuristicSolver::HeuristicSolver(Evaluator* initEvaluator, unsigned int initGoodSolutionsSize, unsigned int initDefaultTemperature) :
	evaluator(initEvaluator), 
	goodSolutionsSize(initGoodSolutionsSize), 
	defaultTemperature(initDefaultTemperature)
{
	Solution currentSolution(initEvaluator, &integerRandomGenerator);
	bitstringRandomGenerator.Random(((Bitstring*)&currentSolution));
	currentSolution.Evaluate();

	goodSolutions.reserve(goodSolutionsSize + 1);
	insertReverseSorted(goodSolutions, currentSolution, goodSolutionsSize);
}

void HeuristicSolver::Iterate()
{
	//In one iteration :
	//Simulated annealing like algorithm searches space for next solution based on best current solution

	long double currentTemperature = this->defaultTemperature;

	Solution currentSolution = goodSolutions[0];
	Solution candidateSolution = goodSolutions[0];

	while (currentTemperature > defaultTemperature / 10)
	{
		candidateSolution = currentSolution;

		for (unsigned int i = 0; i < evaluator->dimesnions.nrOfVars / 4; i++)
		{
			candidateSolution.RandomNeighbour();

			if (candidateSolution < currentSolution)
			{
				currentSolution = candidateSolution;
				currentTemperature = 0;
				break;
			}
			else if (realRandomGenerator.RandomBetween(0, 1) < std::exp(- MyMath::Abslute
				( (currentSolution.GetEval() - candidateSolution.GetEval()) / currentTemperature ) ))
			{
				currentSolution = candidateSolution;
			}
		}

		currentTemperature = currentTemperature * 0.9;
	}

	//Hill climbing is applied on found solution

	//while (currentSolution.FirstImproovement()) {}

	insertReverseSorted(goodSolutions, currentSolution, goodSolutionsSize);
}

void HeuristicSolver::SearchGoodSolutionSpace()
{
	unsigned int targetSolutionIndex = integerRandomGenerator.RandomBetween(1, goodSolutionsSize - 1);

	Solution currentSolution = goodSolutions[0];
	Solution candidateSolution = goodSolutions[0];
	Solution targetSolution = goodSolutions[targetSolutionIndex];

	bool hasImprooved = false;

	for (unsigned int i = 0; i < evaluator->dimesnions.nrOfVars; i++)
	{
		if (realRandomGenerator.RandomBetween(0, 1) < 
			(long double)i / (long double)evaluator->dimesnions.nrOfVars * 0.8)
		{
			candidateSolution.MoveTowards(targetSolution);
		}
		else
		{
			candidateSolution.RandomNeighbour();
		}

		if (candidateSolution < currentSolution)
		{
			currentSolution = candidateSolution;
			hasImprooved = true;
		}
	}

	if (hasImprooved)
	{
		while (currentSolution.FirstImproovement()) {}
		insertReverseSorted(goodSolutions, currentSolution, goodSolutionsSize);
	}
}

long double HeuristicSolver::GetBest()
{
	return goodSolutions[0].GetEval();
}