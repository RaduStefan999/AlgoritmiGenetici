#include "Bitstring.h"

BitstringDimesnions::BitstringDimesnions(long double a, long double b, unsigned int d, unsigned int axes)
{
	this->a = a;
	this->b = b;
	this->d = d;
	this->N = (unsigned int)(log2((b - a) * pow(10, d))) + 1;
	this->axes = axes;

	this->bitsLen = this->N * this->axes;

	this->twoToN = 1ull << N;
}

Bitstring::Bitstring(BitstringDimesnions* dimensions) : bits{}
{
	this->dimensions = dimensions;
}

long double Bitstring::GetNumber(unsigned int axis)
{
	VALIDATE(axis < dimensions->axes, 0, "Invalid axis");

	long double number = 0;

	number = dimensions->a + ((double)GetBitstringNumber(axis)) * (dimensions->b - dimensions->a) / ((double)dimensions->twoToN);

	return number;
}

unsigned long long Bitstring::GetBitstringNumber(unsigned int axis)
{
	VALIDATE(axis < dimensions->axes, 0, "Invalid axis");

	unsigned long long bitstringNumber = 0;
	unsigned long long power = 1;

	for (unsigned int i = axis * dimensions->N; i < (axis + 1) * dimensions->N; i++)
	{
		bitstringNumber = bitstringNumber + this->bits[i] * power;
		power = power * 2;
	}

	return bitstringNumber;
}