#pragma once

#include <iostream>
#include <vector>
#include <string>

struct Individual
{
    unsigned int rules[32];
    // TODO: change this to current state
    std::vector<std::vector<std::string>> initialState;

    // TODO: change this to next state
    std::vector<std::vector<std::string>> goalState;
    std::vector<std::vector<std::string>> currentState;
    float fitness = 0;

    Individual() {}
    Individual(unsigned int*, std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>);

    Individual(const Individual&);
    Individual& operator=(const Individual&);

    std::string getInitialState();
    std::string getGoalState();
    std::string getCurrentState();

    static std::string convertStateToString(std::vector<std::vector<std::string>>);
};