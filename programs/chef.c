#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

#include "shared_memory.h"
#include "help_funcs.h"
#include "chef_help.h"



int main(int argc, char const *argv[]) {
    int numOfSalads, id;
    double mantime;
    char *saladsChar = "-n";
    char *mantimeChar = "-m";
    int err;
    char name[6] = "chef";
    struct timeval timeOfDay;
    unsigned int sleeptime;

    // Use current time as  
    // seed for random generator 
    srand(time(NULL)); 

    // Checks that the the conditions are satisfied
    checkCommandArguments(argc, argv, mantimeChar, saladsChar, &numOfSalads, &mantime);

    // Make shared memory segment
	id = shmget(IPC_PRIVATE,10,0666); 
	if (id == -1) 
		perror ("Error creating shared memory\n");
    else 
        printf("Allocated %d\n", id);
    
    // Pointer to struct struct sharedMemory
    SMemorySeg sMemory;

    /* Attach the segment */
	sMemory = (SMemorySeg)shmat(id, (void*)0, 0);
	if ( sMemory == (void *) -1) { 
        perror("Error attaching shared memory\n"); 
        exit(2);
    }

    // Open a folder in misc
    char newFoldName[40] = "../misc/Logs_";
    char buff[10];
    sprintf(buff, "%d", getpid());
    strcat(newFoldName , buff);
    mkdir(newFoldName, 0777);

    // Create a global file and pass it to the shared memory
    char str[18] = "/global_file.txt";
    char newFileName[50];
    strcpy(newFileName, newFoldName);
    strcat(newFileName, str);

    // Initialize all the variables in shared memory
    initializeSharedMemory(sMemory, numOfSalads, newFoldName, newFileName);

    char message[100];
    char temp[2];
    int ingr1 = tomato;     // Default values
    int ingr2 = peper;      // Default values
    int numOfSaladmaker;
    char *timeStr = malloc(256*sizeof(*timeStr));

    // Get time passed since 1970 in secs and msecs
    gettimeofday(&timeOfDay, NULL);
    struct tm *ts;

    // Open the global file
    FILE *fp;
    fp = fopen(newFileName, "a+b");

    while(1) {
        // When all salads are made this is how chef exits the while loop
        if(sMemory->saladsLeft <= 0) {
            // Notify all saladmakers
            for(int i=0 ; i<NUMSMAKERS ; i++)
                sem_post(&(sMemory->notifySaladmakers[i]));
            // Wait till all saladmakers are done making salads
            for(int i=0 ; i<NUMSMAKERS ; i++)
                sem_wait(&(sMemory->notifySaladmakersEnd));
            break;
        }

        // Select the ingredients 
        numOfSaladmaker = selectIngredients(&ingr1, &ingr2);

        strcpy(message, "Selecting ingredients ");
        if((ingr1 == tomato && ingr2 == peper) || (ingr1 == peper && ingr2 == tomato))
            strcat(message,"tomato peper");
        else if((ingr1 == tomato && ingr2 == onion) || (ingr1 == onion && ingr2 == tomato))
            strcat(message,"tomato onion");
        else
            strcat(message,"peper onion");

        gettimeofday(&timeOfDay, NULL);
        ts = gmtime(&timeOfDay.tv_sec);
        convertTimeToString(ts->tm_mday, (ts->tm_hour+GMT)%24, ts->tm_min, ts->tm_sec, timeOfDay.tv_usec/1000, timeStr);
        printf("[%s][%d][%s][%s]\n",timeStr ,getpid(), name, message);

        // Writing in a global file is critical section so I need a mutex
        sem_wait(&(sMemory->writingToGLogMutex));
        fprintf(fp, "[%s][%d][%s][%s]\n",timeStr ,getpid(), name, message);
        fflush(fp);
        sem_post(&(sMemory->writingToGLogMutex));

        char notifyMessage[20] = "Notify saladmaker #";
        sprintf(temp, "%d", numOfSaladmaker+1);
        strcat(notifyMessage, temp);
        strcpy(message, notifyMessage);

        gettimeofday(&timeOfDay, NULL);
        ts = gmtime(&timeOfDay.tv_sec);
        convertTimeToString(ts->tm_mday, (ts->tm_hour+GMT)%24, ts->tm_min, ts->tm_sec, timeOfDay.tv_usec/1000, timeStr);
        printf("[%s][%d][%s][%s]\n",timeStr ,getpid(), name, message);

        // Writing in a global file is critical section so I need a mutex
        sem_wait(&(sMemory->writingToGLogMutex));
        fprintf(fp, "[%s][%d][%s][%s]\n",timeStr ,getpid(), name, message);
        fflush(fp);
        sem_post(&(sMemory->writingToGLogMutex));

        // Notify the saladmaker about the ingredientss
        sem_post(&(sMemory->notifySaladmakers[numOfSaladmaker]));

        // Wait for the saladmaker to take the ingredients
        sem_wait(&(sMemory->notifyChef));

        strcpy(message, "Man time for resting");
        gettimeofday(&timeOfDay, NULL);
        ts = gmtime(&timeOfDay.tv_sec);
        convertTimeToString(ts->tm_mday, (ts->tm_hour+GMT)%24, ts->tm_min, ts->tm_sec, timeOfDay.tv_usec/1000, timeStr);
        printf("[%s][%d][%s][%s]\n",timeStr ,getpid(), name, message);

        // Writing in a global file is critical section so I need a mutex
        sem_wait(&(sMemory->writingToGLogMutex));
        fprintf(fp, "[%s][%d][%s][%s]\n",timeStr ,getpid(), name, message);
        fflush(fp);
        sem_post(&(sMemory->writingToGLogMutex));

        // Rest
        sleeptime = (unsigned int)mantime;
        sleep(sleeptime);
    }
    free(timeStr);

    // Close the global file
    fclose(fp);

    int sum=0;
    for(int i=0 ; i<NUMSMAKERS ; i++)
        sum += sMemory->saladsPerSaladMaker[i];

    printf("\nTotal #salads: [%d]\n", sum);
    
    for(int i=0 ; i<NUMSMAKERS ; i++)
        printf("#salads of salad_maker%d [%d] : [%d]\n", i+1, sMemory->saladmakerPids[i] ,sMemory->saladsPerSaladMaker[i]);

    printTimeIntervals(newFileName);

    freeSharedMemoryData(sMemory);
    
    // Remove segment
	err = shmctl(id, IPC_RMID, 0);
	if (err == -1) 
		perror ("Error removing shared segment");
	else 
		printf("Just Removed Shared Segment. %d\n", (int)(err));

    return 0;
}
