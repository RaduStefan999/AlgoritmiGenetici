#pragma once

#include "Solution.h"
#include "RandomGenerator.h"
#include "Evaluation.h"

struct SolutionStats
{
	long double eval;

	SolutionStats() : eval(0) {};
};

class HeuristicSolver
{
	typedef std::pair<Solution, SolutionStats> SolutionInfo;
	std::vector<SolutionInfo> goodSolutions;

	BitstringRandomGenerator bitstringRandomGenerator;
	
	Evaluator* evaluator;

	unsigned int goodSolutionsSize;

	long double defaultTemperature;
	long double currentTemperature;

	void FirstImproovement(SolutionInfo&);

public:
	HeuristicSolver(Evaluator* initEvaluator, unsigned int initGoodSolutionsSize, unsigned int initDefaultTemperature);

	void Iterate();
	void SearchGoodSolutionSpace();
	long double GetBest();
};

