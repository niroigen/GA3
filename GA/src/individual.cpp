#include "GA/individual.hpp"

#define DEBUG_MODE 0

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#else
#define DEBUG(x)
#endif

Individual::Individual(unsigned int* rules, std::vector<std::vector<std::string>> initialState, std::vector<std::vector<std::string>> goalState)
    : initialState(initialState), goalState(goalState), currentState(initialState)
{
    for (int i = 0; i < 32; i++)
    {
        this->rules[i] = rules[i];
    }
}

Individual::Individual(const Individual& individual)
{
    for (int i = 0; i < 32; i++)
    {
        this->rules[i] = individual.rules[i];
    }

    initialState = individual.initialState;

    goalState = individual.goalState;

    currentState = individual.currentState;

    fitness = individual.fitness;
}

Individual& Individual::operator=(const Individual& individual)
{
    if( this != &individual )
    {
        for (int i = 0; i < 32; i++)
        {
            rules[i] = individual.rules[i];
        }

        initialState = individual.initialState;

        goalState = individual.goalState;

        currentState = individual.currentState;

        fitness = individual.fitness;
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

std::string Individual::convertStateToString(std::vector<std::vector<std::string>> state)
{
    std::string res = "";

    for (int i = 0; i < state.size(); i++)
    {
        for (int j = 0; j < state[i].size(); j++)
        {
            res += state[i][j];
        }
    }

    return res;
}