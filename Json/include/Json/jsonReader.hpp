#pragma once

#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h> // or jsoncpp/json.h , or json/json.h etc.
#include <jsoncpp/json/writer.h>
#include <string>
#include <cstdint>

#include "GA/individual.hpp"

using namespace std;

extern const int NUM_INDIVIDUALS;

void initializePopulation(Individual**);