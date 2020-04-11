#pragma once

#include <iostream>
#include <vector>
#include <string>

struct Individual
{
    unsigned int rules[512];
    // TODO: change this to current state
    unsigned char initialState[256*256];

    // TODO: change this to next state
    unsigned char goalState[256*256];
    unsigned char currentState[256*256];
    unsigned long fitness = 0;

    Individual() {}
    Individual(unsigned int*, unsigned char*, unsigned char*);

    Individual(const Individual&);
    Individual& operator=(const Individual&);

    std::string getInitialState();
    std::string getGoalState();
    std::string getCurrentState();

    void setCurrentState(const unsigned char*);

    static std::string convertStateToString(unsigned char*);
};