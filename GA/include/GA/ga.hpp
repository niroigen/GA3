#pragma once

#include "Json/jsonReader.hpp"
#include "Json/jsonWriter.hpp"
#include "GA/helper.hpp"

extern std::mt19937 eng;
extern const int NUM_INDIVIDUALS;

struct GA
{
    const int MU;
    const int LAMBDA;
    const int k;
    const float CROSSOVER_RATE;
    const float MUTATION_RATE;
    int generation = 0;
    GaHelper* helper;

    Individual** population;
    Individual** matingPool;
    Individual** offsprings;

    void freePopulation(Individual**);
    void freeOffsprings(Individual**);
    
    GA(const int, const int, const int, const float, const float);
    void run();
    ~GA()
    {
        delete helper;
        helper = nullptr;

        delete[] population;
        delete[] matingPool;
        delete[] offsprings;

        population = nullptr;
        matingPool = nullptr;
        offsprings = nullptr;
    }
};