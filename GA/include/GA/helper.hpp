#pragma once

#include <iostream>
#include <random>
#include <algorithm>
#include <thread>
#include <cstdint>
#include <string>
#include "GA/individual.hpp"
#include "GA/crossover.hpp"
#include "GA/mutation.hpp"
#include "GA/fitness.hpp"
#include "GA/parent.hpp"
#include "GA/survivor.hpp"

extern const int NUM_INDIVIDUALS;
extern std::mt19937 eng;

struct GaHelper
{
    const int MU;
    const int LAMBDA;
    const int k;
    const float CROSSOVER_RATE;
    const float MUTATION_RATE;

    GaHelper(const int MU, const int LAMBDA, const int k, const float CROSSOVER_RATE, const float MUTATION_RATE)
         : MU(MU), LAMBDA(LAMBDA), k(k), CROSSOVER_RATE(CROSSOVER_RATE), MUTATION_RATE(MUTATION_RATE)
    {}

    void evaluateFitness(Individual*);
    void evaluatePopulation(Individual**, int size = NUM_INDIVIDUALS);
    void selectParents(Individual**, Individual**);
    static void pickRandomIndividuals(Individual**, Individual**, int);
    void createOffsprings(Individual**, Individual**);
    void survivorSelection(Individual**, Individual**);
    Individual* getRandomParent(Individual**);
    static Individual* findBestIndividual(Individual**, int);
    void performCrossover(Individual*, Individual*, std::uniform_int_distribution<>&);
    void performMutation(Individual*);
    static bool compareIndividual(const Individual*, const Individual*);
    void attemptRules(Individual**, int);
    static void performRule(Individual*, std::uint8_t, std::uint8_t, std::uint8_t);
    static std::string getWindow(int, const unsigned char*);
};