#include "Population.h"

Population::Population(Evaluator* evaluator, unsigned int populationSize) : evaluator(evaluator) 
{
	this->chromosomes.reserve(populationSize);

	for (unsigned int i = 0; i < populationSize; i++)
	{
		Chromosome chromosome(&(evaluator->dimesnions));
		bitstringRandomGenerator.Random((Bitstring*)(&chromosome));
		chromosomes.push_back(chromosome);
	}
}