#include <iostream>
#include <fstream>
#include <iomanip>
#include "HeuristicSolver.h"

void PrintResult(Evaluator*);
void GetResults(long double*, long double& timeAvg, Evaluator*);

int main()
{
    unsigned int dimensions[3] = { 5, 10, 30 };

    for (auto dimension : dimensions)
    {
        DeJongEvaluator dejong(-5.12, 5.12, 10, dimension);
        SchwefelEvaluator schwefel(-500, 500, 10, dimension);
        RastriginEvaluator rastrigin(-5.12, 5.12, 10, dimension);
        MichalewiczEvaluator michalewicz(0, MyMath::pi, 10, dimension);

        PrintResult(&dejong);
        PrintResult(&schwefel);
        PrintResult(&rastrigin);
        PrintResult(&michalewicz);
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

    std::ofstream out("D:\\Work\\AlgoritmiGenetici\\Tema 2\\Results\\" + std::string(fileName));

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

        for (unsigned int j = 0; j < 2000; j++)
        {
            solver.Iterate();
        }

        for (unsigned int j = 0; j < 2000; j++)
        {
            solver.SearchGoodSolutionSpace();
        }

        results[i] = solver.GetBest();

        timeAvg += since<std::chrono::microseconds>(start).count();
    }

    timeAvg = timeAvg / (30 * MyMath::milion);
}