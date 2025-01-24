#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help_funcs.h"



void convertTimeToString(int day, int hours, int minutes, int seconds, int milliseconds, char *str) {
    char *time = malloc(100*sizeof(*time));
    char col[2] = ":";
    char buff[5];
    
    sprintf(buff, "%02d", day);
    strcpy(time, buff);
    strcat(time, col);

    sprintf(buff, "%02d", hours);
    strcat(time, buff);
    strcat(time, col);

    sprintf(buff, "%02d", minutes);
    strcat(time, buff);
    strcat(time, col);

    sprintf(buff, "%02d", seconds);
    strcat(time, buff);
    strcat(time, col);

    sprintf(buff, "%02d", milliseconds);
    strcat(time, buff);

    strcpy(str, time);

    free(time);
}