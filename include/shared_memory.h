#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define GMT (+2)
#define NUMSMAKERS 3


struct sharedMemory {
    int saladsLeft;

    // How many salads each saladmaker made
    int saladsPerSaladMaker[NUMSMAKERS];

    // The pids of each saladmaker
    int saladmakerPids[NUMSMAKERS];

    // Path name for the newly created folder that will contain the log files
    char pathName[50];

    // Path name for the global log file
    char globalFilePath[50];

    // Mutex for lowering the value of salads
    sem_t mutexForSaladsCS;

    // Writing to global log file is critical section and this is the mutex
    sem_t writingToGLogMutex;

    // Notify the 2 chef not finished that the num of salads is 0
    sem_t notifySaladmakersEnd;

    // Notify chef tha I(saladmaker) took the ingredients
    sem_t notifyChef;

    // Notify a saladmaker tha I(chef) have the ingredients he needs
    sem_t notifySaladmakers[NUMSMAKERS];
};

typedef struct sharedMemory *SMemorySeg; 

void initializeSharedMemory(SMemorySeg sMemory, int numOfSalads, char *newFoldName, char *newFileName);

void freeSharedMemoryData(SMemorySeg sMemory);