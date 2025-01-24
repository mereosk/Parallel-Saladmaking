#include "saladmaker_help.h"



void checkCommandArguments(int argc, const char **argv, char *lChar, char *uChar, char *shmidChar, 
        char *ingredientChar, double *lowerBound, double *upperBound, int *shmid, int *ingredient) {
    
    if(argc == 9) {
        if(strcmp(argv[1], lChar) == 0 && strcmp(argv[3], uChar) == 0 && strcmp(argv[5], shmidChar) == 0 && strcmp(argv[7], ingredientChar) == 0) {
            *lowerBound = atof(argv[2]);
            *upperBound = atof(argv[4]);
            *shmid = atoi(argv[6]);
            *ingredient = atoi(argv[8]);
        }
        else if(strcmp(argv[1], uChar) == 0 && strcmp(argv[3], lChar) == 0 && strcmp(argv[5], shmidChar) == 0 && strcmp(argv[7], ingredientChar) == 0) {
            *lowerBound = atof(argv[4]);
            *upperBound = atof(argv[2]);
            *shmid = atoi(argv[6]);
            *ingredient = atoi(argv[8]);
        }
        else if(strcmp(argv[1], uChar) == 0 && strcmp(argv[3], shmidChar) == 0 && strcmp(argv[5], lChar) == 0 && strcmp(argv[7], ingredientChar) == 0) {
            *lowerBound = atof(argv[6]);
            *upperBound = atof(argv[2]);
            *shmid = atoi(argv[4]);
            *ingredient = atoi(argv[8]);
        }
        else if(strcmp(argv[1], lChar) == 0 && strcmp(argv[3], shmidChar) == 0 && strcmp(argv[5], uChar) == 0 && strcmp(argv[7], ingredientChar) == 0) {
            *lowerBound = atof(argv[2]);
            *upperBound = atof(argv[6]);
            *shmid = atoi(argv[4]);
            *ingredient = atoi(argv[8]);
        }
        else if(strcmp(argv[1], shmidChar) == 0 && strcmp(argv[3], uChar) == 0 && strcmp(argv[5], lChar) == 0 && strcmp(argv[7], ingredientChar) == 0) {
            *lowerBound = atof(argv[6]);
            *upperBound = atof(argv[4]);
            *shmid = atoi(argv[2]);
            *ingredient = atoi(argv[8]);
        }
        else if(strcmp(argv[1], shmidChar) == 0 && strcmp(argv[3], lChar) == 0 && strcmp(argv[5], uChar) == 0 && strcmp(argv[7], ingredientChar) == 0) {
            *lowerBound = atof(argv[4]);
            *upperBound = atof(argv[6]);
            *shmid = atoi(argv[2]);
            *ingredient = atoi(argv[8]);
        }
        else if(strcmp(argv[1], lChar) == 0 && strcmp(argv[3], uChar) == 0 && strcmp(argv[5], ingredientChar) == 0 && strcmp(argv[7], shmidChar) == 0) {
            *lowerBound = atof(argv[2]);
            *upperBound = atof(argv[4]);
            *shmid = atoi(argv[8]);
            *ingredient = atoi(argv[6]);
        }
        else if(strcmp(argv[1], uChar) == 0 && strcmp(argv[3], lChar) == 0 && strcmp(argv[5], ingredientChar) == 0 && strcmp(argv[7], shmidChar) == 0) {
            *lowerBound = atof(argv[4]);
            *upperBound = atof(argv[2]);
            *shmid = atoi(argv[8]);
            *ingredient = atoi(argv[6]);
        }
        else if(strcmp(argv[1], uChar) == 0 && strcmp(argv[3], shmidChar) == 0 && strcmp(argv[5], ingredientChar) == 0 && strcmp(argv[7], lChar) == 0) {
            *lowerBound = atof(argv[8]);
            *upperBound = atof(argv[2]);
            *shmid = atoi(argv[4]);
            *ingredient = atoi(argv[6]);
        }
        else if(strcmp(argv[1], lChar) == 0 && strcmp(argv[3], shmidChar) == 0 && strcmp(argv[5], ingredientChar) == 0 && strcmp(argv[7], uChar) == 0) {
            *lowerBound = atof(argv[2]);
            *upperBound = atof(argv[8]);
            *shmid = atoi(argv[4]);
            *ingredient = atoi(argv[6]);
        }
        else if(strcmp(argv[1], shmidChar) == 0 && strcmp(argv[3], uChar) == 0 && strcmp(argv[5], ingredientChar) == 0 && strcmp(argv[7], lChar) == 0) {
            *lowerBound = atof(argv[8]);
            *upperBound = atof(argv[4]);
            *shmid = atoi(argv[2]);
            *ingredient = atoi(argv[6]);
        }
        else if(strcmp(argv[1], shmidChar) == 0 && strcmp(argv[3], lChar) == 0 && strcmp(argv[5], ingredientChar) == 0 && strcmp(argv[7], uChar) == 0) {
            *lowerBound = atof(argv[4]);
            *upperBound = atof(argv[8]);
            *shmid = atoi(argv[2]);
            *ingredient = atoi(argv[6]);
        }
        else if(strcmp(argv[1], lChar) == 0 && strcmp(argv[3], ingredientChar) == 0 && strcmp(argv[5], uChar) == 0 && strcmp(argv[7], shmidChar) == 0) {
            *lowerBound = atof(argv[2]);
            *upperBound = atof(argv[6]);
            *shmid = atoi(argv[8]);
            *ingredient = atoi(argv[4]);
        }
        else if(strcmp(argv[1], uChar) == 0 && strcmp(argv[3], ingredientChar) == 0 && strcmp(argv[5], lChar) == 0 && strcmp(argv[7], shmidChar) == 0) {
            *lowerBound = atof(argv[6]);
            *upperBound = atof(argv[2]);
            *shmid = atoi(argv[8]);
            *ingredient = atoi(argv[4]);
        }
        else if(strcmp(argv[1], uChar) == 0 && strcmp(argv[3], ingredientChar) == 0 && strcmp(argv[5], shmidChar) == 0 && strcmp(argv[7], lChar) == 0) {
            *lowerBound = atof(argv[8]);
            *upperBound = atof(argv[2]);
            *shmid = atoi(argv[6]);
            *ingredient = atoi(argv[4]);
        }
        else if(strcmp(argv[1], lChar) == 0 && strcmp(argv[3], ingredientChar) == 0 && strcmp(argv[5], shmidChar) == 0 && strcmp(argv[7], uChar) == 0) {
            *lowerBound = atof(argv[2]);
            *upperBound = atof(argv[8]);
            *shmid = atoi(argv[6]);
            *ingredient = atoi(argv[4]);
        }
        else if(strcmp(argv[1], shmidChar) == 0 && strcmp(argv[3], ingredientChar) == 0 && strcmp(argv[5], uChar) == 0 && strcmp(argv[7], lChar) == 0) {
            *lowerBound = atof(argv[8]);
            *upperBound = atof(argv[6]);
            *shmid = atoi(argv[2]);
            *ingredient = atoi(argv[4]);
        }
        else if(strcmp(argv[1], shmidChar) == 0 && strcmp(argv[3], ingredientChar) == 0 && strcmp(argv[5], lChar) == 0 && strcmp(argv[7], uChar) == 0) {
            *lowerBound = atof(argv[6]);
            *upperBound = atof(argv[8]);
            *shmid = atoi(argv[2]);
            *ingredient = atoi(argv[4]);
        }
        else if(strcmp(argv[1], ingredientChar) == 0 && strcmp(argv[3], lChar) == 0 && strcmp(argv[5], uChar) == 0 && strcmp(argv[7], shmidChar) == 0) {
            *lowerBound = atof(argv[4]);
            *upperBound = atof(argv[6]);
            *shmid = atoi(argv[8]);
            *ingredient = atoi(argv[2]);
        }
        else if(strcmp(argv[1], ingredientChar) == 0 && strcmp(argv[3], uChar) == 0 && strcmp(argv[5], lChar) == 0 && strcmp(argv[7], shmidChar) == 0) {
            *lowerBound = atof(argv[6]);
            *upperBound = atof(argv[4]);
            *shmid = atoi(argv[8]);
            *ingredient = atoi(argv[2]);
        }
        else if(strcmp(argv[1], ingredientChar) == 0 && strcmp(argv[3], uChar) == 0 && strcmp(argv[5], shmidChar) == 0 && strcmp(argv[7], lChar) == 0) {
            *lowerBound = atof(argv[8]);
            *upperBound = atof(argv[4]);
            *shmid = atoi(argv[6]);
            *ingredient = atoi(argv[2]);
        }
        else if(strcmp(argv[1], ingredientChar) == 0 && strcmp(argv[3], lChar) == 0 && strcmp(argv[5], shmidChar) == 0 && strcmp(argv[7], uChar) == 0) {
            *lowerBound = atof(argv[4]);
            *upperBound = atof(argv[8]);
            *shmid = atoi(argv[6]);
            *ingredient = atoi(argv[2]);
        }
        else if(strcmp(argv[1], ingredientChar) == 0 && strcmp(argv[3], shmidChar) == 0 && strcmp(argv[5], uChar) == 0 && strcmp(argv[7], lChar) == 0) {
            *lowerBound = atof(argv[8]);
            *upperBound = atof(argv[6]);
            *shmid = atoi(argv[4]);
            *ingredient = atoi(argv[2]);
        }
        else if(strcmp(argv[1], ingredientChar) == 0 && strcmp(argv[3], shmidChar) == 0 && strcmp(argv[5], lChar) == 0 && strcmp(argv[7], uChar) == 0) {
            *lowerBound = atof(argv[6]);
            *upperBound = atof(argv[8]);
            *shmid = atoi(argv[4]);
            *ingredient = atoi(argv[2]);
        }
        else {
            printf("Wrong flags\n");
            exit(1);
        }
    }
    else {
        printf("usage: %s -t1 lowerBound -t2 upperBound -s sharedMemoryId -i ingredient\n", argv[0]);
        exit(1);
    }

    if (( *lowerBound <= 0 ) || ( *lowerBound > *upperBound) || (*shmid < 0) || *ingredient < 0 || *ingredient > 2) {
        printf("conditions: lowerBound > 0, lowerBound < upperBound, sharedMemoryId >= 0, ingredient in range of [1,3]\n");
        exit (1); 
    }
}


double timeForMakingSalad(double lowerBound, double upperBound) {
    double random = ((double) rand()) / (double) RAND_MAX;
    double diff = upperBound - lowerBound;
    double r = random * diff;
    return lowerBound + r;
}