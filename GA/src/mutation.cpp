#include "GA/mutation.hpp"

void randomResetting(Individual *offspring, const float MUTATION_RATE)
{
    std::uniform_real_distribution<> distr(0, 1);
    std::uniform_int_distribution<> dist(0, 3);

    for (int i = 0; i < 512; i++)
    {
        auto r = distr(eng);

        if (r <= MUTATION_RATE)
        {
            offspring->rules[i] = dist(eng);
        }
    }
}