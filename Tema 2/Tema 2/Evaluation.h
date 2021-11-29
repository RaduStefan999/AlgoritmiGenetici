#pragma once

#include "Bitstring.h"

class Evaluator
{
public:
	BitstringDimesnions dimesnions;
	virtual long double Evaluate(Bitstring*) = 0;

	Evaluator(long double a, long double b, unsigned int d, unsigned int axes) : dimesnions(a, b, d, axes) {};
};

class DeJongEvaluator : public Evaluator
{
public:
	long double Evaluate(Bitstring* solution) override
	{
		long double result = 0;
		long double number = 0;

		for (unsigned int i = 0; i < dimesnions.axes; i++)
		{
			number = solution->GetNumber(i);
			result += number * number;
		}

		return result;
	}
	DeJongEvaluator(long double a, long double b, unsigned int d, unsigned int axes) : Evaluator(a, b, d, axes) {};
};

