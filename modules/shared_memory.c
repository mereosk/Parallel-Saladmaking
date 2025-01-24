#include "shared_memory.h"


void initializeSharedMemory(SMemorySeg sMemory, int numOfSalads, char *newFoldName, char *newFileName) {
    int retval; 

    sMemory->saladsLeft = numOfSalads;
    //Initialize the array in which lyes the number of salads of each saladmaker
    for(int i=0 ; i<3 ; i++)
        sMemory->saladsPerSaladMaker[i]=0;

    retval = sem_init(&(sMemory->notifyChef), 1, 0);
	if (retval != 0) {
		perror("Couldn't initialize.");
		exit(3);
	}

    // Mutex for keeping the CS safe
    retval = sem_init(&(sMemory->mutexForSaladsCS), 1, 1);
	if (retval != 0) {
		perror("Couldn't initialize.");
		exit(3);
	}

    // Mutex for appending safely in the global file
    retval = sem_init(&(sMemory->writingToGLogMutex), 1, 1);
	if (retval != 0) {
		perror("Couldn't initialize.");
		exit(3);
	}

    retval = sem_init(&(sMemory->notifySaladmakersEnd), 1, 0);
	if (retval != 0) {
		perror("Couldn't initialize.");
		exit(3);
	}

    int ingCount = 0;
    for (ingCount = 0; ingCount < 3; ingCount++) {
        sem_init(&(sMemory->notifySaladmakers[ingCount]), 1, 0);
    }

    strcpy(sMemory->pathName, newFoldName);
    strcpy(sMemory->globalFilePath, newFileName);
}


void freeSharedMemoryData(SMemorySeg sMemory) {
    sem_destroy(&(sMemory->notifyChef));
    sem_destroy(&(sMemory->mutexForSaladsCS));
    sem_destroy(&(sMemory->writingToGLogMutex));
    sem_destroy(&(sMemory->writingToGLogMutex));
    for (int i = 0; i < NUMSMAKERS; i++) {
        sem_destroy(&(sMemory->notifySaladmakers[i]));
    }
}