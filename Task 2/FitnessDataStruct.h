#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structs
typedef struct {
	char filename[18];
	char fileformat[6];
} Filename;

typedef struct {
	char date[11];
	char time[6];
	char steps[4];
} FITNESS_DATA;

// Define any additional variables here
FILE *fp = NULL;
Filename file;
FITNESS_DATA FITNESS_DATAS;
char option;
char file_name[50];
char buff[21];
char ff_buff[21];
char fl_buff[21];
char time1[6];
char time2[6];
char start_time[17];
char end_time[17];
char current_start_time[17];
char current_end_time[17];
char feweststeps_data[11];
char feweststeps_time[6];
int namestatment;
int formatstatment;
int feweststeps = 100000;
int largeststeps = 0;
int meanstepcount;
int quit = 0;
int counter = 0;
int linecounter = 0;
int periodcounter = 0;
int max_periodcounter = 0;
int statment = 0;
char hour[3];
char minute[3];
char rightname[] = "FitnessData_2023";
char rightformat[] = "csv";

// Help functions
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    char *inputCopy = strdup(input);
    
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    free(inputCopy);
}


