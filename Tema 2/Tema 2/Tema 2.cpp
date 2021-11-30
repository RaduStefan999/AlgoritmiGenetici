#include <iostream>
#include "Population.h"

int main()
{
    DeJongEvaluator dejong(-5.12, 5.12, 10, 10);

    Population population(&dejong, 100, 5);

    for (unsigned int i = 0; i < 100; i++)
    {
        population.Evolve();
    }

    return 0;
}