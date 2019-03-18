//
// Created by bamam on 3/15/2019.
//

#include "userLogs.h"

void createUserLog(char *username){
    char * filename = (char *) malloc(1 + strlen(username)+ strlen(".log"));
    strcpy(filename, username);
    strcat(filename, ".log");
    FILE *fp;
    fp = fopen(filename, "a+"); // a+ (create + append) option will allow appending which is useful in a log file
    if (fp == NULL) {
        printf("Could not open file %s", filename);
    }
    fprintf(fp, "Im logging something ..\n");
}

void readUserLog(char *username){
    char * filename = (char *) malloc(1 + strlen(username)+ strlen(".log"));
    strcpy(filename, username);
    strcat(filename, ".log");
    FILE *fp;
    char line[300];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
    }

    fgets(line, 300, fp);       //gets file header
    printf("%s\n", line);
    fclose(fp);
}