#include "chef_help.h"
#include "help_funcs.h"


void checkCommandArguments(int argc, char const **argv, char *mantimeChar, char *saladsChar, int *numOfSalads, double *mantime) {
    if(argc == 5) {
        if(strcmp(argv[1], mantimeChar) == 0 && strcmp(argv[3], saladsChar)==0) {
            *numOfSalads = atoi(argv[2]);
            *mantime = atof(argv[4]);
        }
        else if(strcmp(argv[1], saladsChar) == 0 && strcmp(argv[3], mantimeChar) == 0) {
            *mantime = atof(argv[4]);
            *numOfSalads = atoi(argv[2]);
        }
        else {
            printf("Wrong flag\n");
            exit(1);
        }
    }
    else {
        printf("usage: %s -n numOfSlds -u mantime\n", argv[0]);
        exit(1);
    }

    if (( *numOfSalads < 1 ) || (*mantime <= 0)) {
        printf("conditions: numOfSalads > 0 and mantime > 0\n");
        exit (1); 
    }
}


void printTimeIntervals(char *pathName) {
    int counter;
    FILE *fp;
    char *line = malloc(256*sizeof(*line));
    char delim[3] = "][";
    char *token;

    // Data in each line
    char time[50];
    int saladmaker;
    char message[50];
    char *startMessage = "Get ingredients";
    char *endMessage = "End making salad";

    fp = fopen(pathName, "r");

    // Whenever a saladmaker is active his/her value will be true
    bool salad1, salad2, salad3;

    // Initialization
    salad1 = false; salad2 = false; salad3 = false;
    printf("\n");

    // Read the global file line by line
    while(fgets(line, 256, fp) != NULL) {

        // get the first token
        token = strtok(line, delim);
        strcpy(time, token);

        counter = 0;
        while( token != NULL ) {
            token = strtok(NULL, delim);
            
            // I want to extract the number of saladmaker which is in the end of the string
            // After that to convert it to int, i cast and subtract from it the ACSII code of zero
            if(counter == 1) 
                saladmaker = (int)(token[strlen(token)-1] - 48);
            else if(counter == 2)
                strcpy(message, token);

            counter++;
        }

        // Message is "Get ingredients" 
        if(strcmp(message, startMessage) == 0) {
            if(saladmaker == 1 && salad2 == false && salad3 == false) {
                salad1 = true;
            }
            else if((saladmaker == 1 && salad2 == true && salad3 == false) || (saladmaker == 1 && salad2 == false && salad3 == true)) {
                printf("[%s,", time);
                salad1 = true;
            }
            else if(saladmaker == 1 && salad2 == true && salad3 == true) {
                printf("%s] 2 concurrent saladmakers\n", time);
                printf("[%s,", time);
                salad1 = true;
            }
            else if(saladmaker == 2 && salad1 == false && salad3 == false) {
                salad2 = true;
            }
            else if((saladmaker == 2 && salad1 == true && salad3 == false) || (saladmaker == 2 && salad1 == false && salad3 == true)) {
                printf("[%s,", time);
                salad2 = true;
            }
            else if(saladmaker == 2 && salad1 == true && salad3 == true) {
                printf("%s] 2 concurrent saladmakers\n", time);
                printf("[%s,", time);
                salad2 = true;
            }
            else if(saladmaker == 3 && salad2 == false && salad1 == false) {
                salad3 = true;
            }
            else if((saladmaker == 3 && salad2 == true && salad1 == false) || (saladmaker == 3 && salad2 == false && salad1 == true)) {
                printf("[%s,", time);
                salad3 = true;
            }
            else if(saladmaker == 3 && salad2 == true && salad1 == true) {
                printf("%s] 2 concurrent saladmakers\n", time);
                printf("[%s,", time);
                salad3 = true;
            }
        }       // If it the message is "End making salad"
        else if(strcmp(message, endMessage) == 0) {
            if(saladmaker == 1 && salad2 == false && salad3 == false) {
                salad1 = false;
            }
            else if((saladmaker == 1 && salad2 == true && salad3 == false) || (saladmaker == 1 && salad2 == false && salad3 == true)) {
                printf("%s] 2 concurrent saladmakers\n", time);
                salad1 = false;
            }
            else if(saladmaker == 1 && salad2 == true && salad3 == true) {
                printf("%s] 3 concurrent saladmakers\n", time);
                printf("[%s,", time);
                salad1 = false;
            }
            else if(saladmaker == 2 && salad1 == false && salad3 == false) {
                salad2 = false;
            }
            else if((saladmaker == 2 && salad1 == true && salad3 == false) || (saladmaker == 2 && salad1 == false && salad3 == true)) {
                printf("%s] 2 concurrent saladmakers\n", time);
                salad2 = false;
            }
            else if(saladmaker == 2 && salad1 == true && salad3 == true) {
                printf("%s] 3 concurrent saladmakers\n", time);
                printf("[%s,", time);
                salad2 = false;
            }
            else if(saladmaker == 3 && salad2 == false && salad1 == false) {
                salad3 = false;
            }
            else if((saladmaker == 3 && salad2 == true && salad1 == false) || (saladmaker == 3 && salad2 == false && salad1 == true)) {
                printf("%s] 2 concurrent saladmakers\n", time);
                salad3 = false;
            }
            else if(saladmaker == 3 && salad2 == true && salad1 == true) {
                printf("%s] 3 concurrent saladmakers\n", time);
                printf("[%s,", time);
                salad3 = false;
            }
        }
    }
    free(line);
    fclose(fp);
}


int selectIngredients(int *ingr1, int *ingr2) {
    int num;
    int temp1, temp2;

    // Don't put the same ingredients as the last catch in the table
    while(1) {
        num = rand()%3;
        if(num == 0) {
            temp1 = peper;
            temp2 = onion;
        }
        else if(num == 1) {
            temp1 = tomato;
            temp2 = onion;
        }
        else {
            temp1 = tomato;
            temp2 = peper;
        }

        if(*ingr1 == temp1 && *ingr2 == temp2)
            continue;
        break;
    }
    *ingr1 = temp1;
    *ingr2 = temp2;

    return num;
}