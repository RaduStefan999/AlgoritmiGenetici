#include "Solution.h"

bool Solution::FirstImproovement()
{
	long double bestEval = this->evaluator->Evaluate(((Bitstring*)this));
	long double currentEval = 0;

	for (unsigned int i = 0; i < this->dimensions->N; i++)
	{
		this->bits[i] = !(this->bits[i]);

		currentEval = this->evaluator->Evaluate(((Bitstring*)this));

		if (currentEval < bestEval)
		{
			bestEval = currentEval;
			break;
		}

		this->bits[i] = !(this->bits[i]);
	}

	return eval;
}