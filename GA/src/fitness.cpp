#include "GA/fitness.hpp"

#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#define WAIT std::cin.get();
#else
#define DEBUG(x)
#define WAIT
#endif

void defaultFitnessFunction(Individual* individual)
{
    unsigned long fitness = 0;

    for (int i = 0; i < 256*256; i++)
    {
        if (individual->currentState[i] != individual->goalState[i])
        {
            fitness++;
        }
    }

    individual->fitness = fitness;
}