#pragma once

#include <math.h>
#include "RandomGenerator.h"
#include "Defines.h"

#define BITS_ARRAY_SIZE 64 * 30

struct BitstringDimesnions
{
	unsigned int nrOfVars;

	BitstringDimesnions(unsigned int initNrOfVars) : nrOfVars(initNrOfVars) {};
};

class Bitstring
{
protected:
	//std::bitset would maybe work better
	bool bits[BITS_ARRAY_SIZE];

	BitstringDimesnions* dimensions;
public:
	Bitstring() = default;
	Bitstring(BitstringDimesnions* dimensions);
	
	inline bool& operator[] (unsigned int index) { return bits[index]; }

	friend BitstringRandomGenerator;
};

