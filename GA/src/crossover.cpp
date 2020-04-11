#include "GA/crossover.hpp"

void uniformCrossover(Individual *offspring1, Individual *offspring2,
                      std::uniform_int_distribution<>& distr)
{
    const int size = 32;
    int crossover_arr[size];

    for (int i = 0; i < size; i++)
    {
        crossover_arr[i] = distr(eng);
    }

    for (int i = 0; i < size; i++)
    {
        if (crossover_arr[i] < 0.5)
        {
            int temp = offspring1->rules[i];

            offspring1->rules[i] = offspring2->rules[i];
            offspring2->rules[i] = temp;
        }
    }
}

void twoPointCrossover(Individual *offspring1, Individual *offspring2,
                      std::uniform_int_distribution<>& distr)
{
    int r1, r2;

    do
    {
        r1 = distr(eng);
        r2 = distr(eng);
    } while(r1 == r2);

    int startIdx = r1, endIdx = r2;

    if (r2 < r1)
    {
        startIdx = r2;
        endIdx = r1;
    }

    for (int i = startIdx; i <= endIdx; i++)
    {
        int temp = offspring1->rules[i];

        offspring1->rules[i] = offspring2->rules[i];
        offspring2->rules[i] = temp;
    }
}