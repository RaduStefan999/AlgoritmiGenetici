#pragma once

#include "Bitstring.h"
#include "MyMath.h"
#include <fstream>
#include <string>

class Evaluator
{
public:
	BitstringDimesnions dimesnions;
	virtual long double Evaluate(Bitstring*) = 0;
	virtual void GetTitle(char*) = 0;

	Evaluator(unsigned int initNrOfVars) : dimesnions(initNrOfVars) {};
};

class ThreeSatEvaluator : public Evaluator
{
	const char* clausesPath;
	const char* evaluatorName;

	short int (*clauses)[3];

public:
	long double Evaluate(Bitstring* solution) override;
	void GetTitle(char*) override;
	ThreeSatEvaluator(unsigned int initNrOfVars, const char* initClausesPath, const char* initEvaluatorName);
	~ThreeSatEvaluator();
};