#pragma once

#include <vector>
#include <math.h>
#include "RandomGenerator.h"
#include "Defines.h"

struct BitstringDimesnions
{
	unsigned int N; //len(bits)
	long double a; //[a, b]
	long double b; //[a, b]
	unsigned int d; // precission
	unsigned int axes; //nr de dimensiuni - axele OX, OY, OZ ..
	unsigned long long twoToN;

	BitstringDimesnions(long double a, long double b, unsigned int d, unsigned int axes);
};

class Bitstring
{
protected:
	std::vector<bool> bits;
	BitstringDimesnions* dimensions;
	unsigned long long GetBitstringNumber(unsigned int axis);
public:
	Bitstring(BitstringDimesnions* dimensions);
	long double GetNumber(unsigned int axis);

	friend BitstringRandomGenerator;
};
