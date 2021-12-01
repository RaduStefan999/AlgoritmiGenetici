#include "Chromosome.h"

void Chromosome::Mutate()
{
	unsigned int index = integerRandomGenerator->RandomBetween(0, dimensions->bitsLen - 1);
	bits[index] = !bits[index];
}

void CrossOver(Chromosome& a, Chromosome& b)
{
	unsigned int index = a.integerRandomGenerator->RandomBetween(1, a.dimensions->bitsLen - 2);

	bool aux = false;

	for (unsigned int i = index; i < a.dimensions->bitsLen; i++)
	{
		aux = a.bits[i];
		a.bits[i] = b.bits[i];
		b.bits[i] = aux;
	}
}