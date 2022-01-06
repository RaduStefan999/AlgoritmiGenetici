#include <iostream>
#include <fstream>
#include <iomanip>
#include "HeuristicSolver.h"

void PrintResult(Evaluator*);
void GetResults(long double*, long double& timeAvg, Evaluator*);

struct Input
{
    unsigned int nrOfVars;
    const char* inputPath;
    const char* inputName;
};

int main()
{
    Input input[3] =
    {
        {250, "E:\\Radu\\work\\master\\Tema 3\\Inputs\\uf250-01.cnf", "HARD-uf250-01"},
        {250, "E:\\Radu\\work\\master\\Tema 3\\Inputs\\uf250-02.cnf", "HARD-uf250-02"},
        {250, "E:\\Radu\\work\\master\\Tema 3\\Inputs\\uf250-03.cnf", "HARD-uf250-03"}
    };

    for (unsigned int i = 0; i < 3; i++)
    {
        ThreeSatEvaluator threeSatEvaluator(input[i].nrOfVars, input[i].inputPath, input[i].inputName);
        PrintResult(&threeSatEvaluator);
    }

    return 0;
}

void PrintResult(Evaluator* eval)
{
    long double results[30];
    long double timeAvg = 0;

    GetResults(results, timeAvg, eval);

    long double minim, maxim, avg, sd;
    minim = maxim = avg = results[0];
    sd = 0;

    for (unsigned int i = 1; i < 30; i++)
    {
        avg += results[i];

        if (results[i] < minim)
        {
            minim = results[i];
        }
        if (results[i] > maxim)
        {
            maxim = results[i];
        }
    }

    avg = avg / 30;

    for (unsigned int i = 0; i < 30; i++)
    {
        sd += (results[i] - avg) * (results[i] - avg);
    }

    sd = sqrt(sd / 30);

    char fileName[100];
    eval->GetTitle(fileName);

    std::ofstream out("E:\\Radu\\work\\master\\Tema 3\\Results\\" + std::string(fileName));

    out << std::setprecision(10)
        << "min : " << minim << '\n'
        << "max : " << maxim << '\n'
        << "avg : " << avg << '\n'
        << "sd : " << sd << '\n'
        << "timeAvg : " << timeAvg;

    out.close();
}

void GetResults(long double* results, long double& timeAvg, Evaluator* eval)
{
    timeAvg = 0;

    for (unsigned int i = 0; i < 30; i++)
    {
        auto start = std::chrono::steady_clock::now();

        HeuristicSolver solver(eval, 3, 2000);

        for (unsigned int j = 0; j < 200000; j++)
        {
            solver.Iterate();
        }

        for (unsigned int j = 0; j < 2000; j++)
        {
            //solver.SearchGoodSolutionSpace();
        }

        results[i] = solver.GetBest();

        timeAvg += since<std::chrono::microseconds>(start).count();
    }

    timeAvg = timeAvg / (30 * MyMath::milion);
}