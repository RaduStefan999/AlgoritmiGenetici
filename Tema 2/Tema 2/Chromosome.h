#pragma once

#include "Bitstring.h"

class Chromosome : public Bitstring
{
	IntegerRandomGenerator<unsigned int>* integerRandomGenerator;

public:
	Chromosome(BitstringDimesnions* dimensions, IntegerRandomGenerator<unsigned int>* integerRandomGenerator) : 
		Bitstring(dimensions), integerRandomGenerator(integerRandomGenerator) {}

	void Mutate();
	friend void CrossOver(Chromosome& a, Chromosome& b);
};