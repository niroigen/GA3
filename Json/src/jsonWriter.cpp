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

    std::ofstream file_id;
    std::ofstream ans;
    file_id.open("bestIndividual.json");
    ans.open("ans.txt");
    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(best);
    ans << currentState;
    ans.close();
    file_id.close();
}