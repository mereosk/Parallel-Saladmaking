#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void checkCommandArguments(int argc, char const **argv, char *mantimeChar, char *saladsChar, int *numOfSalads, double *mantime);

void printTimeIntervals(char *pathName);

int selectIngredients(int *ingr1, int *ingr2);