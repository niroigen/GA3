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
    std::string goalState = individual->getGoalState();
    std::string currentState = individual->getCurrentState();

    int fitness_table[9][9] = {0};

    for (int row = 0; row < 9; row++)
    {
        fitness_table[row][0] = row;
    }

    for (int col = 0; col < 9; col++)
    {
        fitness_table[0][col] = col;
    }

    for (int row = 0; row < 9; row++)
    {
        if (row - 1 >= int(individual->currentState.size()))
        {
            fitness_table[8][8] = 10;
            break;
        }
        for (int col = 0; col < 9; col++)
        {
            if (row != 0 && col != 0)
            {
                char val1 = currentState[row - 1];
                char val2 = goalState[col - 1];
                
                if (val1 == val2)
                {
                    fitness_table[row][col] = fitness_table[row-1][col-1];
                }
                else
                {
                    fitness_table[row][col] = std::min({fitness_table[row-1][col] + 1, fitness_table[row][col-1] + 1, fitness_table[row-1][col-1] + 2});
                }
            }
        }
    }
    
    individual->fitness = fitness_table[8][8];
}