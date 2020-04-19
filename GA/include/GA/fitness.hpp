#pragma once

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <thread>
#include "GA/individual.hpp"

void defaultFitnessFunction(Individual*);
static void evalPartial(Individual* individual, unsigned int start_idx, unsigned int end_idx, unsigned long* counter);