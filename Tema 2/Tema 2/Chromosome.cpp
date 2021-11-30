#include "Chromosome.h"

void Chromosome::Mutate()
{
	unsigned int index = integerRandomGenerator->RandomBetween(0, dimensions->N - 1);
	bits[index] = !bits[index];
}

void CrossOver(Chromosome& a, Chromosome& b)
{
	unsigned int index = a.integerRandomGenerator->RandomBetween(1, a.dimensions->N - 2);

	bool aux = false;

	for (unsigned int i = index; i < a.dimensions->N; i++)
	{
		aux = a.bits[i];
		a.bits[i] = b.bits[i];
		b.bits[i] = aux;
	}
}