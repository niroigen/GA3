#include "GA/helper.hpp"

#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#define WAIT std::cin.get();
#else
#define DEBUG(x)
#define WAIT
#endif

void GaHelper::evaluatePopulation(Individual** population, int size)
{
    for (int i = 0; i < size; i++)
    {
        evaluateFitness(population[i]);
    }
}

void GaHelper::evaluateFitness(Individual* individual)
{
    defaultFitnessFunction(individual);
}

void GaHelper::survivorSelection(Individual** population, Individual** offsprings)
{
    replacePopulation(population, offsprings, LAMBDA);
}

void GaHelper::pickRandomIndividuals(Individual** randomIndividuals, Individual** population, int k)
{
    std::uniform_int_distribution<> distr(0, NUM_INDIVIDUALS - 1);

    for (int i = 0; i < k; i++)
    {
        int randIdx = distr(eng);

        randomIndividuals[i] = population[randIdx];
    }
}

Individual* GaHelper::findBestIndividual(Individual** individuals, int numIndividuals)
{
    unsigned int bestIdx = 0;
    float bestFitness = individuals[0]->fitness;
    for (int i = 1; i < numIndividuals; i++)
    {
        if(individuals[i]->fitness < bestFitness)
        {
            bestIdx = i;
            bestFitness = individuals[i]->fitness;
        }
    }

    return individuals[bestIdx];
}

void GaHelper::selectParents(Individual** matingPool, Individual** population)
{
    tournamentSelection(matingPool, population, k, MU, findBestIndividual, pickRandomIndividuals);
}

Individual* GaHelper::getRandomParent(Individual** matingPool)
{
    std::uniform_int_distribution<> distr(0, MU - 1);

    Individual* test = matingPool[distr(eng)];

    return matingPool[distr(eng)];
}

bool GaHelper::compareIndividual(const Individual* i1, const Individual* i2)
{
    return i1->fitness < i2->fitness;
}

void GaHelper::createOffsprings(Individual** offsprings, Individual** matingPool)
{
    int i = 0;

    std::uniform_real_distribution<> dist(0, 1);
    
    std::uniform_int_distribution<> distr(0, 512);

    while(i < LAMBDA)
    {
        Individual* parent1 = GaHelper::getRandomParent(matingPool);
        Individual* parent2 = GaHelper::getRandomParent(matingPool);

        float r = dist(eng);

        Individual* offspring1 = new Individual(*parent1);
        Individual* offspring2 = new Individual(*parent2);

        if (r <= CROSSOVER_RATE)
        {
            GaHelper::performCrossover(offspring1, offspring2, distr);
        }

        GaHelper::performMutation(offspring1);
        GaHelper::performMutation(offspring2);

        offsprings[i++] = offspring1;
        offsprings[i++] = offspring2;
    }
}

void GaHelper::performCrossover(Individual *offspring1, Individual *offspring2,
                                std::uniform_int_distribution<>& distr)
{
    twoPointCrossover(offspring1, offspring2, distr);
}

void GaHelper::performMutation(Individual *offspring)
{
    randomResetting(offspring, MUTATION_RATE);
}

char toChar(const unsigned char* currentState, int idx)
{
    return (char) (currentState[idx] + 48);
}

std::string GaHelper::getWindow(int startIdx, const unsigned char* currentState)
{
    std::string res(9,'0');

    res[0] = toChar(currentState, startIdx);
    res[1] = toChar(currentState, (startIdx + 1) % (256*256));
    res[2] = toChar(currentState, (startIdx + 2) % (256*256));
    res[3] = toChar(currentState, (256 + startIdx) % (256*256));
    res[4] = toChar(currentState, (256 + startIdx + 1) % (256*256));
    res[5] = toChar(currentState, (256 + startIdx + 2) % (256*256));
    res[6] = toChar(currentState, (512 + startIdx) % (256*256));
    res[7] = toChar(currentState, (512 + startIdx + 1) % (256*256));
    res[8] = toChar(currentState, (512 + startIdx + 2) % (256*256));

    return res;
}

bool isGoalStateEqualToCurrentState(unsigned char* currentState, unsigned char* goalState)
{
    for (int i = 0; i < 256*256; i++)
    {
        if (currentState[i] != goalState[i]) return false;
    }

    DEBUG("WOWWW");
    WAIT;
    return true;
}

void GaHelper::attemptRules(Individual** population, int size)
{
    bool solutionFound = false;
    
    for (int i = 0; i < size && !solutionFound; i++)
    {
        Individual* currentIndividual = population[i];

        unsigned char nextState[256*256];

        for (int i = 0; i < 256*256; i++)
        {
            nextState[i] = currentIndividual->initialState[i];
            currentIndividual->currentState[i] = currentIndividual->initialState[i];
        }

        for (int test = 0; test < 1 && !solutionFound; test++)
        {
            for (int startIdx = 0; startIdx < 256*256 && !solutionFound; startIdx++)
            {
                std::string window = GaHelper::getWindow(startIdx, currentIndividual->currentState);

                const int rule = std::stoi(window, nullptr, 2);

                int rule_to_perform = currentIndividual->rules[rule];

                int middleIdx = (256 + startIdx + 1) % (256*256);

                switch(rule_to_perform)
                {
                    case 0:
                    nextState[middleIdx] = 0;
                    break;
                    case 1:
                    nextState[middleIdx] = 1;
                    break;
                }

                solutionFound = isGoalStateEqualToCurrentState(nextState, population[0]->goalState);

                if (solutionFound) 
                {
                    currentIndividual->setCurrentState(nextState);
                    evaluateFitness(currentIndividual);
                    break;
                }
            }

            currentIndividual->setCurrentState(nextState);
        }
    }
}
