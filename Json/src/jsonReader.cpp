#include "Json/jsonReader.hpp"

#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#define WAIT std::cin.get();
#else
#define DEBUG(x)
#define WAIT
#endif

void initializePopulation(Individual** population) {
    ifstream ifs("CellularAutomata.json");

    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings

    unsigned char initialState [256*256];
    unsigned char goalState [256*256];

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            initialState[256 * i + j] = obj[0][i][j].asInt() > 0;
            goalState[256 * i + j] = obj[1][i][j].asInt() > 0;
        }
    }

    DEBUG("DONE");

    unsigned int rules[512];

    for (int i = 0; i <  NUM_INDIVIDUALS; i++)
    {
        for (int j = 0; j < 512; j++)
        {
            int rule;
            for (auto const& id : obj[i+2][j].getMemberNames())
            {
                rule = obj[i+2][j][id].asInt();
            }

            rules[j] = rule;
        }

        Individual* originalIndividual = new Individual(rules, initialState, goalState);

        population[i] = originalIndividual;
    }

    DEBUG("DONE INITIALIZATION");
}