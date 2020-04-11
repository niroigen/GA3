#include "GA/survivor.hpp"

void replacePopulation(Individual** population, Individual** offsprings, const int LAMBDA)
{
    int numToReplace = NUM_INDIVIDUALS;

    if (LAMBDA < NUM_INDIVIDUALS) {
        numToReplace = LAMBDA;
    }
    for (int i = NUM_INDIVIDUALS - 1; i > (NUM_INDIVIDUALS - 1) - numToReplace; i--)
    {
        population[i] = new Individual(*offsprings[i]);
    }
}