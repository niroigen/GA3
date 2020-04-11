#include "GA/parent.hpp"

void tournamentSelection(Individual** matingPool, Individual** population, const int k, const int MU,
                         Individual* (*funcBestIndividual)(Individual**, int),
                         void (*funcPickRandomIndividuals)(Individual**, Individual**, int))
{
    unsigned int currentMember = 0;

    while(currentMember < MU)
    {
        Individual *randomIndividuals[k];

        (*funcPickRandomIndividuals)(randomIndividuals, population, k);

        Individual* bestIndividual = (*funcBestIndividual)(randomIndividuals, k);

        #if DEBUG
        std::cout << bestIndividual->fitness << '\n';
        #endif

        matingPool[currentMember] = bestIndividual;
        currentMember++;
    }
}