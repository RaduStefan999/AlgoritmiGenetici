#pragma once

#include "Solution.h"
#include "RandomGenerator.h"
#include "Evaluation.h"

class HeuristicSolver
{
	Evaluator* evaluator;
	BitstringRandomGenerator bitstringRandomGenerator;
	IntegerRandomGenerator<unsigned int> integerRandomGenerator;
	RealRandomGenerator<long double> realRandomGenerator;

	unsigned int goodSolutionsSize;

	long double defaultTemperature;

	std::vector<Solution> goodSolutions;

public:
	HeuristicSolver(Evaluator* initEvaluator, unsigned int initGoodSolutionsSize, unsigned int initDefaultTemperature);

	void Iterate();
	void SearchGoodSolutionSpace();
	long double GetBest();
};

