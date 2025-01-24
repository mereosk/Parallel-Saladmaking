#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void checkCommandArguments(int argc, const char **argv, char *lChar, char *uChar, char *shmidChar, 
        char *ingredientChar, double *lowerBound, double *upperBound, int *shmid, int *ingredient);


double timeForMakingSalad(double lowerBound, double upperBound);