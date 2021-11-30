#pragma once

#include "Chromosome.h"
#include "RandomGenerator.h"
#include "Evaluation.h"

struct ChromosomeStats
{
	long double eval;
	long double individualProb;
	long double cumulatedProb;

	bool isMemberOfTheElite;

	ChromosomeStats() : eval(0), individualProb(0), cumulatedProb(0), isMemberOfTheElite(false) {};
};

class Population
{
	typedef std::pair<Chromosome, ChromosomeStats> Individual;
	std::vector<Individual> individuals;
	std::vector<Individual> eliteIndividuals;

	BitstringRandomGenerator bitstringRandomGenerator;
	IntegerRandomGenerator<unsigned int> integerRandomGenerator;
	RealRandomGenerator<long double> realRandomGenerator;

	Evaluator* evaluator;

	long double GetFitness(Individual& individual);

	unsigned int populationSize;
	unsigned int eliteSize;
	unsigned int generation;

	long double totalFitness;

	void FortuneWheelEval();
	void EnsureElitism();
	void SelectNewIndividuals();
	void MutateIndividuals();
	void CrossOverIndividuals();

public:
	Population(Evaluator* evaluator, unsigned int populationSize, unsigned int nrOfEliteIndividuals);
	void Evolve();
};

