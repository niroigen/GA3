#pragma once

#include <random>
#include "GA/individual.hpp"

extern std::mt19937 eng;

void uniformCrossover(Individual*, Individual*, std::uniform_int_distribution<>&);
void twoPointCrossover(Individual*, Individual*, std::uniform_int_distribution<>&);