#pragma once

#include "Chromosome.h"
#include "RandomGenerator.h"
#include "Evaluation.h"

class Population
{
	std::vector<Chromosome> chromosomes;

	BitstringRandomGenerator bitstringRandomGenerator;
	NumberRandomGenerator<unsigned int> numberRandomGenerator;

	Evaluator* evaluator;

public:
	Population(Evaluator* evaluator, unsigned int populationSize);
};

