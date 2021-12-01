#include <iostream>
#include "Population.h"

int main()
{
    DeJongEvaluator dejong(-5.12, 5.12, 10, 30);
    SchwefelEvaluator schwefel(-500, 500, 10, 30);
    RastriginEvaluator rastrigin(-5.12, 5.12, 10, 30);
    MichalewiczEvaluator michalewicz(0, MyMath::pi, 10, 30);

    Population population(&michalewicz, 1000, 10, false);

    for (unsigned int i = 0; i < 1000; i++)
    {
        population.Evolve();
        std::cout << population.GetBest() << std::endl;
    }

    std::cout << population.GetBest();

    return 0;
}