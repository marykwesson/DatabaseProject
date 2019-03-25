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

void deleteUserLog(char *username){
    char * filename = (char *) malloc(1 + strlen(username)+ strlen(".log"));
    strcpy(filename, username);
    strcat(filename, ".log");
    int status = remove(filename);
    if (status == 0) {
        printf("%s file deleted successfully.\n", filename);
    }
    else{
        printf("Unable to delete the file\n");
    }
}

int exists(char *username) {
    FILE *file;
    char * filename = (char *) malloc(1 + strlen(username)+ strlen(".log"));
    strcpy(filename, username);
    strcat(filename, ".log");
    file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    } else {
        return 0;
    }
}

/*void writeUserLog(Movie* movie){
    printf("\nTitle\t\t\tYear\tRuntime\tGenres\tDate\tType\t\n");
    for (int i = 0; i < 10; i++){
        if (movie->primaryTitle != NULL){
            printLine(movie->primaryTitle, movie->year, movie->runtime, movie->genres, movie->date, movie->type);
        }
    }
}*/

void printLine(char *title, char *year, char *runtime, char *genres, char *date, char *type){
    printf("\t%s\t\t\t%s\t%s\t%s\t\t%s\t%s\t%s\n", title, year, runtime, genres, date, type);
}