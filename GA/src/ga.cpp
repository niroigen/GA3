#include "GA/ga.hpp"

#define DEBUG_MODE 1
#define LOG(x) std::cout << x << std::endl;

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#define WAIT std::cin.get();
#else
#define DEBUG(x)
#define WAIT
#endif

GA::GA(const int MU, const int LAMBDA, const int k, const float CROSSOVER_RATE, const float MUTATION_RATE)
    : MU(MU), LAMBDA(LAMBDA), k(k), CROSSOVER_RATE(CROSSOVER_RATE), MUTATION_RATE(MUTATION_RATE)
{
    population = new Individual*[NUM_INDIVIDUALS];
    matingPool = new Individual*[MU];
    offsprings = new Individual*[LAMBDA];

    DEBUG("Starting to initialize instance of GA")
    helper = new GaHelper(MU, LAMBDA, k, CROSSOVER_RATE, MUTATION_RATE);

    DEBUG("Finished initializing instance of GA")
}

void GA::freePopulation(Individual** population)
{
    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete population[i];
        population[i] = nullptr;
    }
}

void GA::freeOffsprings(Individual** offsprings)
{
    for (int i = 0; i < LAMBDA; i++)
    {
        delete offsprings[i];
        offsprings[i] = nullptr;
    }
}

void GA::run()
{
    DEBUG("Starting to initialize population")
    initializePopulation(population);

    DEBUG("Initialized population")
    helper->evaluatePopulation(population);

    #if DEBUG_MODE
    Individual* bestIndividualInit = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);
    DEBUG("BEST INDIVIDUAL");
    DEBUG(bestIndividualInit->fitness);
    #endif

    for (generation = 0; generation < 200; generation++)
    {
        // Selecting parents for next generation
        helper->selectParents(matingPool, population);
        // Creating offsprings off of the potential parents

        helper->createOffsprings(offsprings, matingPool);

        // Attempting rules
        helper->attemptRules(offsprings, LAMBDA);

        // Evaluating their fitness level
        helper->evaluatePopulation(offsprings, LAMBDA);

        // Freeing the population
        freePopulation(population);

        // Sorting the by fitness
        std::sort(offsprings, offsprings+LAMBDA, GaHelper::compareIndividual);

        // Replace the population with NUM_INDIVIDUAL's best offspring
        helper->survivorSelection(population, offsprings);

        // Freeing the offspring that will no longer be used
        freeOffsprings(offsprings);

        #if DEBUG_MODE
        Individual* bestIndividualInit = population[0];
        DEBUG("Generation : " + std::to_string(generation) + " BEST SO FAR " + std::to_string(bestIndividualInit->fitness));

        if(bestIndividualInit->fitness == 0) break;
        #endif
    }

    Individual* bestIndividual = helper->findBestIndividual(population, NUM_INDIVIDUALS);
    std::cout << bestIndividual->fitness << ',' << std::flush;

    DEBUG("Has taken " + std::to_string(generation) + " generations to complete")

    outputBestIndividual(bestIndividual);

    LOG("Found best individual, please check file");

    freePopulation(population);
}
