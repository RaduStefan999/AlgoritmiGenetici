#include "Solution.h"

bool Solution::FirstImproovement()
{
	this->eval = this->evaluator->Evaluate(((Bitstring*)this));

	long double currentEval = 0;

	for (unsigned int i = 0; i < this->dimensions->nrOfVars; i++)
	{
		this->bits[i] = !(this->bits[i]);

		currentEval = this->evaluator->Evaluate(((Bitstring*)this));

		if (currentEval < eval)
		{
			eval = currentEval;
			return true;
		}

		this->bits[i] = !(this->bits[i]);
	}

	return false;
}

bool Solution::BestImproovement()
{
	this->eval = this->evaluator->Evaluate(((Bitstring*)this));

	long double currentEval = 0;

	long double bestEval = eval;
	unsigned int bestEvalIndex = 0;

	for (unsigned int i = 0; i < this->dimensions->nrOfVars; i++)
	{
		this->bits[i] = !(this->bits[i]);

		currentEval = this->evaluator->Evaluate(((Bitstring*)this));

		if (currentEval < bestEval)
		{
			bestEval = currentEval;
			bestEvalIndex = i;
		}

		this->bits[i] = !(this->bits[i]);
	}

	if (bestEval > eval)
	{
		this->bits[bestEvalIndex] = !(this->bits[bestEvalIndex]);
		eval = bestEval;
		return true;
	}

	return false;
}

bool Solution::RandomNeighbour()
{
	unsigned int randomPozFlip = integerRandomGenerator->RandomBetween(0, dimensions->nrOfVars - 1);
	this->bits[randomPozFlip] = !(this->bits[randomPozFlip]);

	this->eval = this->evaluator->Evaluate(((Bitstring*)this));

	return true;
}

bool Solution::MoveTowards(const Solution& obj)
{
	unsigned int randomPozStep = integerRandomGenerator->RandomBetween(0, dimensions->nrOfVars - 1);
	this->bits[randomPozStep] = obj.bits[randomPozStep];

	this->eval = this->evaluator->Evaluate(((Bitstring*)this));

	return true;
}

bool Solution::InitFrom(const Solution& obj)
{
	memcpy(this, &obj, sizeof(Solution));
	return true;
}