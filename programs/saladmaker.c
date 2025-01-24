#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

#include "shared_memory.h"
#include "help_funcs.h"
#include "saladmaker_help.h"


int mkdir(const char *pathname, mode_t mode);


int main(int argc, char const *argv[]) {
    int shmid, ingredient;
    double lowerBound, upperBound;
    char *lChar = "-t1";
    char *uChar = "-t2";
    char *shmidChar = "-s";
    char *ingredientChar = "-i";
    char name[12] = "saladmaker";
    struct timeval timeOfDay;
    char *timeString = malloc(254*sizeof(*timeString));
    unsigned int makeSaladTime;

    srand(time(NULL));

    // Checks that the the conditions are satisfied
    checkCommandArguments(argc, argv, lChar, uChar, shmidChar, ingredientChar, &lowerBound, &upperBound, &shmid, &ingredient);

    // Time needed to make a salad
    double saladmakerTime;
    saladmakerTime = timeForMakingSalad(lowerBound, upperBound);

    // Update the name with the correct number
    char buffer[2];
    sprintf(buffer, "%d", ingredient+1);
    strcat(name, buffer);

    SMemorySeg sMem;
    /* Attach the segment */
	sMem = shmat(shmid, (void*) 0,0);
    if ( sMem == (void *) -1) { 
        perror("Error attaching shared memory\n"); 
        exit(2);
    }

    // Put the pid in the shared memory segment
    sMem->saladmakerPids[ingredient] = getpid();

    // Open private log file
    char newFileName[100];
    strcpy(newFileName, sMem->pathName);
    char buff[2];
    char buff1[40] = "/salad";
    char buff2[20] = "_log.txt";
    sprintf(buff, "%d", ingredient+1);
    strcat(newFileName, buff1);
    strcat(newFileName, buff);
    strcat(newFileName, buff2);

    // Private log file
    FILE *pfp;
    pfp = fopen(newFileName, "w");

    // Global log file
    FILE *gfp;
    gfp = fopen(sMem->globalFilePath, "a+b");

    // Get time passed since 1970 in secs and msecs
    gettimeofday(&timeOfDay, NULL);
    struct tm *ts;
    
    char message[100];
    while(1) {

        strcpy(message, "Waiting for ingredients");
        gettimeofday(&timeOfDay, NULL);
        ts = gmtime(&timeOfDay.tv_sec);
        convertTimeToString(ts->tm_mday, (ts->tm_hour+GMT)%24, ts->tm_min, ts->tm_sec, timeOfDay.tv_usec/1000, timeString);
        printf("[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);
        fprintf(pfp, "[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);

        // Writing in a global file is critical section so I need a mutex
        sem_wait(&(sMem->writingToGLogMutex));
        fprintf(gfp, "[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);
        fflush(gfp);
        sem_post(&(sMem->writingToGLogMutex));
    
        // Wait for the ingredients
        sem_wait(&(sMem->notifySaladmakers[ingredient]));

        if(sMem->saladsLeft <= 0){
            sem_post(&(sMem->notifyChef));
            sem_post(&(sMem->notifySaladmakersEnd));
            break;
        }

        // Notify the chef that I took the ingredients
        sem_post(&(sMem->notifyChef));

        strcpy(message, "Get ingredients");
        gettimeofday(&timeOfDay, NULL);
        ts = gmtime(&timeOfDay.tv_sec);
        convertTimeToString(ts->tm_mday, (ts->tm_hour+GMT)%24, ts->tm_min, ts->tm_sec, timeOfDay.tv_usec/1000, timeString);
        printf("[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);
        fprintf(pfp, "[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);

        // Writing in a global file is critical section so I need a mutex
        sem_wait(&(sMem->writingToGLogMutex));
        fprintf(gfp, "[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);
        fflush(gfp);
        sem_post(&(sMem->writingToGLogMutex));

           
        strcpy(message, "Start making salad");
        gettimeofday(&timeOfDay, NULL);
        ts = gmtime(&timeOfDay.tv_sec);
        convertTimeToString(ts->tm_mday, (ts->tm_hour+GMT)%24, ts->tm_min, ts->tm_sec, timeOfDay.tv_usec/1000, timeString);
        printf("[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);
        fprintf(pfp, "[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);

        // Writing in a global file is critical section so I need a mutex
        sem_wait(&(sMem->writingToGLogMutex));
        fprintf(gfp, "[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);
        fflush(gfp);
        sem_post(&(sMem->writingToGLogMutex));

        makeSaladTime = (unsigned int)saladmakerTime;
        sleep(makeSaladTime);

        sem_wait(&(sMem->mutexForSaladsCS));
        // Substract 1 from the salads left from share memory
        sMem->saladsLeft--;
        sem_post(&(sMem->mutexForSaladsCS));
        sMem->saladsPerSaladMaker[ingredient]++;

        strcpy(message, "End making salad");
        gettimeofday(&timeOfDay, NULL);
        ts = gmtime(&timeOfDay.tv_sec);
        convertTimeToString(ts->tm_mday, (ts->tm_hour+GMT)%24, ts->tm_min, ts->tm_sec, timeOfDay.tv_usec/1000, timeString);
        printf("[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);
        fprintf(pfp, "[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);

        // Writing in a global file is critical section so I need a mutex
        sem_wait(&(sMem->writingToGLogMutex));
        fprintf(gfp, "[%s][%d][%s][%s]\n",timeString ,getpid(), name, message);
        fflush(gfp);
        sem_post(&(sMem->writingToGLogMutex));

        // Check if the number of salads left is 0 and if it is exit the loop
        // printf("Salads left are %d\n", sMem->saladsLeft);
        if(sMem->saladsLeft <= 0){
            sem_post(&(sMem->notifyChef));
            sem_post(&(sMem->notifySaladmakersEnd));
            break;
        }
    }

    fclose (pfp);
    fclose(gfp);

    free(timeString);


    int err;
    // Detach segment
	err = shmdt((void *) sMem);
	if (err == -1) 
        perror ("Error detatching shared memory segment\n");
	else 
        printf("Detachment of Shared Segment %d\n", err);
    
    return 0;
}
