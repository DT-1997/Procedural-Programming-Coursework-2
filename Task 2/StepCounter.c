#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Function declaration
void check_filename();
void count_records();
void find_feweststeps();
void find_largeststeps();
void find_meanstepcount();
void find_longestperiod();

// Main function
int main(){
    while (quit != 1)
    {
        printf("Option Menu: Enter A~E to operate the program, enter any other character to exit the program!\n");
        scanf("%s", &option);
        switch (option){
            case 'A':
                check_filename();
                break;
            case 'B':
                count_records();
                break;
            case 'C':
                find_feweststeps();
                break;
            case 'D':
                find_largeststeps();
                break;
            case 'E':
                find_meanstepcount();
                break;
            case 'F':
                find_longestperiod();
                break;
            default:
                quit = 1;
                fclose(fp);
            }  
    }
    return 0;
}

void check_filename(){
    printf("Input filename:");
    scanf("%s",&file_name);
    tokeniseRecord(file_name,".",file.filename,file.fileformat,NULL);
	namestatment = strcmp(file.filename,rightname);
    formatstatment = strcmp(file.fileformat,rightformat);
    if (namestatment != 0)
    {
        printf("Wrong file name,please modify it!\n");
    }
    else if (formatstatment != 0)
    {
        printf("Wrong file format,please modify it!\n");
    }
    else{
        printf("Successfully opened file!\n");
        fp = fopen("FitnessData_2023.csv","r");
    }
}

void count_records(){
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%s", buff) != EOF)
    {
        counter++;
    }
    printf("Total records:%d\n",counter);
    counter = 0;
}

void find_feweststeps(){
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%s", buff) != EOF)
    {
        tokeniseRecord(buff,",",FITNESS_DATAS.date,FITNESS_DATAS.time,FITNESS_DATAS.steps);
        if (atoi(FITNESS_DATAS.steps) < feweststeps)
        {
            feweststeps = atoi(FITNESS_DATAS.steps);
            strcpy(ff_buff,FITNESS_DATAS.date);
            strcat(ff_buff," ");
            strcat(ff_buff,FITNESS_DATAS.time);
        }
    }
    printf("Fewest steps:%s\n",ff_buff);
}

void find_largeststeps(){
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%s", buff) != EOF)
    {
        tokeniseRecord(buff,",",FITNESS_DATAS.date,FITNESS_DATAS.time,FITNESS_DATAS.steps);
        if (atoi(FITNESS_DATAS.steps) > largeststeps)
        {
            largeststeps = atoi(FITNESS_DATAS.steps);
            strcpy(fl_buff,FITNESS_DATAS.date);
            strcat(fl_buff," ");
            strcat(fl_buff,FITNESS_DATAS.time);
        }
    }
    printf("Largest steps:%s\n",fl_buff);
}

void find_meanstepcount(){
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%s", buff) != EOF)
    {
        counter++;
        tokeniseRecord(buff,",",FITNESS_DATAS.date,FITNESS_DATAS.time,FITNESS_DATAS.steps);
        meanstepcount += atoi(FITNESS_DATAS.steps);
    }
    meanstepcount /= counter;
    printf("Mean step count:%d\n",meanstepcount);
    counter = 0;
}

void find_longestperiod(){
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%s", buff) != EOF)
    {
        counter++;
        tokeniseRecord(buff,",",FITNESS_DATAS.date,FITNESS_DATAS.time,FITNESS_DATAS.steps);
        if (atoi(FITNESS_DATAS.steps) > 500)
        {
            periodcounter++;
            if (linecounter == 0)
            {
                linecounter = counter;
            }
            if (counter != linecounter)
            {
                if (counter - linecounter == 1)
                {
                    NULL;
                }
                else
                {
                    statment = 0;
                    periodcounter = 0;
                    linecounter = counter;
                }
            }
            if (statment == 0)
            {
                strcpy(current_start_time,FITNESS_DATAS.date);
                strcat(current_start_time," ");
                strcat(current_start_time,FITNESS_DATAS.time);
                statment = 1;
            }
            if (counter - linecounter == 1)
            {
                linecounter = counter;
                strcpy(current_end_time,FITNESS_DATAS.date);
                strcat(current_end_time," ");
                strcat(current_end_time,FITNESS_DATAS.time);
            }
        }
        if (periodcounter > max_periodcounter)
        {
            max_periodcounter = periodcounter;
            strcpy(start_time,current_start_time);
            strcpy(end_time,current_end_time);
        }
    }
    printf("Longest period start:%s\nLongest period end:%s\n",start_time,end_time);
    counter = 0;
}