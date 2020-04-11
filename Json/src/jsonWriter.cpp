#include "Json/jsonWriter.hpp"
#include <string>

void outputBestIndividual(Individual* bestIndividual)
{
    std::string initialState = bestIndividual->getInitialState();
    std::string goalState = bestIndividual->getGoalState();
    std::string currentState = bestIndividual->getCurrentState();

    Json::Value best;
    best["Initial State"] = initialState;
    best["Goal State"] = goalState;
    best["Current State"] = currentState;

    best["rules"] = Json::Value(Json::arrayValue);
    Json::Value &rules = best["rules"];

    for (int i = 0; i < 512; i++)
    {
        rules[i] = bestIndividual->rules[i];
    }
    // population["puzzle"] = obj["0"]["puzzle"];
    // best["length"] = bestIndividual->frameLength;
    // best["width"] = bestIndividual->frameWidth;
    // best["pieces"] = bestIndividual->size;

    // best["puzzle"] = Json::Value(Json::arrayValue);
    // Json::Value &puzzle = best["puzzle"];

    // for (int i = 0; i < bestIndividual->size; i++)
    // {
    //     puzzle[i] = Json::Value(Json::arrayValue);

    //     puzzle[i][0] = bestIndividual->tiles[i].x;
    //     puzzle[i][1] = bestIndividual->tiles[i].y;
    //     puzzle[i][2] = bestIndividual->tiles[i].l;
    //     puzzle[i][3] = bestIndividual->tiles[i].w;
    // }

    std::ofstream file_id;
    file_id.open("bestIndividual.json");
    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(best);
    file_id.close();
}