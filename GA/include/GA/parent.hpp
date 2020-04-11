#pragma once

#include "GA/individual.hpp"

void tournamentSelection(Individual**, Individual**, const int, const int,
                         Individual* (*funcBestIndividual)(Individual**, int),
                         void (*funcPickRandomIndividuals)(Individual**, Individual**, int));