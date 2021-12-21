#include "HeuristicSolver.h"

HeuristicSolver::HeuristicSolver(Evaluator* initEvaluator, unsigned int initGoodSolutionsSize, unsigned int initDefaultTemperature) :
	evaluator(initEvaluator), 
	goodSolutionsSize(initGoodSolutionsSize), 
	defaultTemperature(initDefaultTemperature)
{
	goodSolutions.reserve(goodSolutionsSize);


}

void HeuristicSolver::Iterate()
{

}

void HeuristicSolver::SearchGoodSolutionSpace()
{

}

long double HeuristicSolver::GetBest()
{

}

void HeuristicSolver::FirstImproovement(SolutionInfo& solutionInfo)
{
	auto fn = [](Solution* solution, unsigned int index, void* context) -> bool
	{
		SolutionStats* solutionStats = (SolutionStats*)(context);

		if (solutionStats->eval > evaluator->)
	};

	solutionInfo.first.TakeOneStepInEachDirection(fn, &(solutionInfo.second));
}