#pragma once

#include "Bitstring.h"
#include "MyMath.h"
#include <string>

class Evaluator
{
public:
	BitstringDimesnions dimesnions;
	virtual long double Evaluate(Bitstring*) = 0;
	virtual void GetTitle(char*) = 0;

	Evaluator(long double a, long double b, unsigned int d, unsigned int axes) : dimesnions(a, b, d, axes) {};
};

class DeJongEvaluator : public Evaluator
{
public:
	long double Evaluate(Bitstring* solution) override;
	void GetTitle(char*) override;
	DeJongEvaluator(long double a, long double b, unsigned int d, unsigned int axes) : Evaluator(a, b, d, axes) {};
};

class SchwefelEvaluator : public Evaluator
{
public:
	long double Evaluate(Bitstring* solution) override;
	void GetTitle(char*) override;
	SchwefelEvaluator(long double a, long double b, unsigned int d, unsigned int axes) : Evaluator(a, b, d, axes) {};
};

class RastriginEvaluator : public Evaluator
{
public:
	long double Evaluate(Bitstring* solution) override;
	void GetTitle(char*) override;
	RastriginEvaluator(long double a, long double b, unsigned int d, unsigned int axes) : Evaluator(a, b, d, axes) {};
};

class MichalewiczEvaluator : public Evaluator
{
public:
	long double Evaluate(Bitstring* solution) override;
	void GetTitle(char*) override;
	MichalewiczEvaluator(long double a, long double b, unsigned int d, unsigned int axes) : Evaluator(a, b, d, axes) {};
};
