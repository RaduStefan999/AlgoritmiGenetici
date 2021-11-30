#include "Chromosome.h"

void Chromosome::Mutate()
{
	unsigned int index = integerRandomGenerator->RandomBetween(0, dimensions->N - 1);
	bits[index] = !bits[index];
}

void CrossOver(Chromosome& a, Chromosome& b)
{
	unsigned int index = a.integerRandomGenerator->RandomBetween(1, a.dimensions->N - 2);


}