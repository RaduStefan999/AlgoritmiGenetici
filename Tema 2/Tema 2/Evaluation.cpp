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
		result += sin(number) * pow(sin(((i + 1) * number*number) / MyMath::pi), 2*dimesnions.axes);
	}
	
	return -result;
}

void DeJongEvaluator::GetTitle(char* str)
{
	std::string name = ("DeJong_" + std::to_string(dimesnions.axes)).c_str();
	memcpy(str, name.c_str(), name.size() + 1);
}

void SchwefelEvaluator::GetTitle(char* str)
{
	std::string name = ("Schwefel_" + std::to_string(dimesnions.axes)).c_str();
	memcpy(str, name.c_str(), name.size() + 1);
}

void RastriginEvaluator::GetTitle(char* str)
{
	std::string name = ("Rastrigin_" + std::to_string(dimesnions.axes)).c_str();
	memcpy(str, name.c_str(), name.size() + 1);
}

void MichalewiczEvaluator::GetTitle(char* str)
{
	std::string name = ("Michalewicz_" + std::to_string(dimesnions.axes)).c_str();
	memcpy(str, name.c_str(), name.size() + 1);
}