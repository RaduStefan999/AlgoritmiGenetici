#pragma once

#include "Bitstring.h"
#include "Evaluation.h"

class Solution : public Bitstring
{
	Evaluator* evaluator;
	long double eval;

	IntegerRandomGenerator<unsigned int>* integerRandomGenerator;

public:
	Solution(Evaluator* initEvaluator, IntegerRandomGenerator<unsigned int>* initIntegerRandomGenerator) :
		Bitstring(&(initEvaluator->dimesnions)), evaluator(initEvaluator), 
		integerRandomGenerator(initIntegerRandomGenerator), eval(0) {}
	
	Solution(const Solution& obj) { InitFrom(obj); }
	Solution& operator = (const Solution& obj) { InitFrom(obj); return *this; }
	bool InitFrom(const Solution& obj);
	
	bool FirstImproovement();
	bool BestImproovement();
	bool RandomNeighbour();
	bool MoveTowards(const Solution& obj);

	inline long double GetEval() { return eval; }
	inline long double Evaluate() { this->eval = this->evaluator->Evaluate(((Bitstring*)this)); return eval; }

	friend bool operator > (const Solution& lh, const Solution& rh) { return lh.eval > rh.eval; }
	friend bool operator < (const Solution& lh, const Solution& rh) { return lh.eval < rh.eval; }
};