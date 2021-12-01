#pragma once

#include "Bitstring.h"
#include "MyMath.h"

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
	long double Evaluate(Bitstring* solution) override;
	DeJongEvaluator(long double a, long double b, unsigned int d, unsigned int axes) : Evaluator(a, b, d, axes) {};
};

class SchwefelEvaluator : public Evaluator
{
public:
	long double Evaluate(Bitstring* solution) override;
	SchwefelEvaluator(long double a, long double b, unsigned int d, unsigned int axes) : Evaluator(a, b, d, axes) {};
};

class RastriginEvaluator : public Evaluator
{
public:
	long double Evaluate(Bitstring* solution) override;
	RastriginEvaluator(long double a, long double b, unsigned int d, unsigned int axes) : Evaluator(a, b, d, axes) {};
};

class MichalewiczEvaluator : public Evaluator
{
public:
	long double Evaluate(Bitstring* solution) override;
	MichalewiczEvaluator(long double a, long double b, unsigned int d, unsigned int axes) : Evaluator(a, b, d, axes) {};
};
