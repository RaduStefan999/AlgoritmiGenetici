#include "Evaluation.h"

ThreeSatEvaluator::ThreeSatEvaluator(unsigned int initNrOfVars, const char* initClausesPath, const char* initEvaluatorName) :
	Evaluator(initNrOfVars), clausesPath(initClausesPath) , evaluatorName(initEvaluatorName)
{
	clauses = new short int[initNrOfVars][3];

	std::ifstream fin(clausesPath);

	char buffer[512];

	do 
	{
		fin.getline(buffer, 511);

	} while (buffer[0] != 'p');

	for (unsigned int i = 0; i < dimesnions.nrOfVars; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			fin >> clauses[i][j];
			fin.getline(buffer, 511);
		}
	}

	fin.close();
}

long double ThreeSatEvaluator::Evaluate(Bitstring* solution)
{
	unsigned int nrOfFailedClauses = 0;
	bool satisfied = false;

	for (unsigned int i = 0; i < dimesnions.nrOfVars; i++)
	{
		satisfied = false;

		for (unsigned int j = 0; j < 3; j++)
		{
			if (clauses[i][j] > 0)
			{
				satisfied |= (*solution)[MyMath::IntAbsolute(clauses[i][j]) - 1];
			}
			else
			{
				satisfied |= !((*solution)[MyMath::IntAbsolute(clauses[i][j]) - 1]);
			}
		}

		if (!satisfied)
		{
			nrOfFailedClauses++;
		}
	}

	return nrOfFailedClauses;
}

void ThreeSatEvaluator::GetTitle(char* str)
{
	std::string name = ("3SAT_" + std::string(this->evaluatorName)).c_str();
	memcpy(str, name.c_str(), name.size() + 1);
}

ThreeSatEvaluator::~ThreeSatEvaluator()
{
	delete[] clauses;
}