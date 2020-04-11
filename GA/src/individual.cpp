#include "GA/individual.hpp"

#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#define WAIT std::cin.get();
#else
#define DEBUG(x)
#define WAIT
#endif

Individual::Individual(unsigned int* rules, unsigned char* initialState, unsigned char* goalState)
{
    for (int i = 0; i < 512; i++)
    {
        this->rules[i] = rules[i];
    }

    for (int i = 0; i < 256*256; i++)
    {
        this->initialState[i] = (int) initialState[i];
        this->goalState[i] = (int) goalState[i];
        this->currentState[i] = (int) initialState[i];
    }
}

Individual::Individual(const Individual& individual)
{
    for (int i = 0; i < 512; i++)
    {
        this->rules[i] = (int) individual.rules[i];
    }

    for (int i = 0; i < 256*256; i++)
    {
        this->initialState[i] = individual.initialState[i];
        this->goalState[i] = individual.goalState[i];
        this->currentState[i] = individual.initialState[i];
    }

    fitness = individual.fitness;
}

Individual& Individual::operator=(const Individual& individual)
{
    if( this != &individual )
    {
        for (int i = 0; i < 512; i++)
        {
            rules[i] = individual.rules[i];
        }

        for (int i = 0; i < 256*256; i++)
        {
            this->initialState[i] = individual.initialState[i];
            this->goalState[i] = individual.goalState[i];
            this->currentState[i] = individual.initialState[i];
        }
    }
    return *this;
}

std::string Individual::getInitialState()
{
    return convertStateToString(initialState);
}

std::string Individual::getCurrentState()
{
    return convertStateToString(currentState);
}

std::string Individual::getGoalState()
{
    return convertStateToString(goalState);
}

std::string Individual::convertStateToString(unsigned char* state)
{
    std::string res(256*256, '0');

    for (int i = 0; i < 256*256; i++)
    {
        if (state[i] == 1) res[i] = '1';
    }

    return res;
}

void Individual::setCurrentState(const unsigned char* curr_state)
{
    for (int i = 0; i < 256*256; i++)
    {
        this->currentState[i] = curr_state[i];
    }
}