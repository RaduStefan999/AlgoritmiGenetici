#pragma once

#include "Bitstring.h"

class Chromosome : public Bitstring
{
public:
	void Mutate();
	Chromosome(BitstringDimesnions* dimensions) : Bitstring(dimensions) {};
};

