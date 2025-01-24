#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// It converts time microsecond to hours, minutes, seconds, milliconds
// void convertMicro(int *hours, int *minutes, int *seconds, int *milliseconds, int time);
enum ingredients{tomato, peper, onion};


void convertTimeToString(int day,int hours, int minutes, int seconds, int milliseconds, char *str);