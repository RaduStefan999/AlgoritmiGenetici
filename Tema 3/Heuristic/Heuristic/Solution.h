#pragma once

#include "Bitstring.h"
#include "Evaluation.h"

class Solution : public Bitstring
{
	Evaluator* evaluator;
	long double eval;

public:
	Solution(BitstringDimesnions* dimensions, Evaluator* initEvaluator) :
		Bitstring(dimensions), evaluator(initEvaluator), eval(0) {}
	
	long double FirstImproovement();
	long double BestImproovement();
};