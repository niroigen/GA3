#pragma once

#include <random>
#include "GA/individual.hpp"

extern std::mt19937 eng;

void randomResetting(Individual*, const float);