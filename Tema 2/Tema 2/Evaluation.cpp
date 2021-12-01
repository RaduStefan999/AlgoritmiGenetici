#include "Evaluation.h"

long double DeJongEvaluator::Evaluate(Bitstring* solution)
{
	long double result = 0;
	long double number = 0;

	for (unsigned int i = 0; i < dimesnions.axes; i++)
	{
		number = solution->GetNumber(i);
		result += number * number;
	}

	return result;
}

long double SchwefelEvaluator::Evaluate(Bitstring* solution)
{
	long double result = 0;
	long double number = 0;

	for (unsigned int i = 0; i < dimesnions.axes; i++)
	{
		number = solution->GetNumber(i);
		result += (-number) * sin(sqrt(MyMath::Abslute(number)));
	}

	return result;
}

long double RastriginEvaluator::Evaluate(Bitstring* solution)
{
	long double result = 0;
	long double number = 0;

	for (unsigned int i = 0; i < dimesnions.axes; i++)
	{
		number = solution->GetNumber(i);
		result += number * number - 10 * cos(2 * MyMath::pi * number);
	}

	return 10ull * dimesnions.axes + result;
}

long double MichalewiczEvaluator::Evaluate(Bitstring* solution)
{
	long double result = 0;
	long double number = 0;

	for (unsigned int i = 0; i < dimesnions.axes; i++)
	{
		number = solution->GetNumber(i);
		result += sin(number) * pow(sin((i * number*number) / MyMath::pi), 2*dimesnions.axes);
	}
	
	return -result;
}