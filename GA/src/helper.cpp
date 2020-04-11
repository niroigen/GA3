#include "GA/helper.hpp"

#define DEBUG_MODE 0

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
    
    std::uniform_int_distribution<> distr(0, 31);

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

std::string GaHelper::getWindow(int startIdx, const std::string& currentState)
{
    std::string res = "00000";

    for (int i = 0; i < 5; i++)
    {
        res[i] = currentState[(startIdx + i) % currentState.length()];
    }

    return res;
}

bool isGoalStateEqualToCurrentState(std::string currentState,std::string goalState)
{
    if (currentState.size() != goalState.length()) return false;
    else
    {
        for (int i = 0; i < currentState.length(); i++)
        {
            if (currentState[i] != goalState[i]) return false;
        }

        return true;
    }
}

void GaHelper::attemptRules(Individual** population, int size)
{
    bool solutionFound = false;
    for (int i = 0; i < size && !solutionFound; i++)
    {
        Individual* currentIndividual = population[i];

        DEBUG("START");
        DEBUG("");

        std::string cur = currentIndividual->getInitialState();

        DEBUG("CURRENT INDIVIDUAL");
        DEBUG(cur);
        DEBUG("");

        for (int test = 0; test < 30 && !solutionFound; test++)
        {
            std::string currentState = currentIndividual->getInitialState();
            auto nextState = currentIndividual->initialState;
            std::string goalState = currentIndividual->getGoalState();

            for (int startIdx = 0; startIdx < currentState.size() && !solutionFound; startIdx++)
            {
                std::string window = GaHelper::getWindow(startIdx, currentState);

                const int rule = std::stoi(window, nullptr, 2);

                int rule_to_perform = currentIndividual->rules[rule];

                int middleIdx = (startIdx + 2) % currentState.size();

                switch(rule_to_perform)
                {
                    case 0:
                    nextState[middleIdx] = 0;
                    break;
                    case 1:
                    nextState[middleIdx] = 1;
                    break;
                }

                std::string nextStateStr = Individual::convertStateToString(nextState);
                
                DEBUG(rule_to_perform);
                DEBUG(nextStateStr);

                solutionFound = isGoalStateEqualToCurrentState(nextStateStr, goalState);

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
