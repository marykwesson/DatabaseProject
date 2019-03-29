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
    //fprintf(fp, "Im logging somethig ..\n");
    fprintf(fp,"%-200s %-6s %-7s %-30s %-12s %-9s \n", "Title", "Year", "Runtime", "Genres", "Date", "Type");
    //fprintf (fp,"%25s%6s%7s%25s%12s%10s\n", "Title", "Year", "Runtime", "Genres", "Date", "Type");
    fclose(fp);
}

void readUserLog(char *username){
    char * filename = (char *) malloc(1 + strlen(username)+ strlen(".log"));
    strcpy(filename, username);
    strcat(filename, ".log");
    FILE *fp;
    //char line[300];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
    }
    //Node *userArray[50];
    Node* userTree = NULL;
    userTree = readLogIntoTree(userTree, username);
    //int temp = getCount(userTree);
    //printf("%d", temp);
    printf("%-200s %-6s %-7s %-30s %-12s %-9s \n", "Title", "Year", "Runtime", "Genres", "Date", "Type");
    printUserLog(userTree);
    //printUserLog(userTree);
    //ReadLogIntoArray(userArray, username);
    //printf("%-25s %-6s %-7s %-30s %-12s %-9s \n", "Title", "Year", "Runtime", "Genres", "Date", "Type");
/*    for(int i = 0; i < 50; i++){
        if(userArray[i]->primaryTitle != NULL){
            printLine(userArray[i]);
        }
    }*/
    fclose(fp);
}

void printUserLog(Node *node) {
    if (node == NULL) {
        return;
    }
    printUserLog(node->left);
    printf("%-250s %-6s %-7s %-30s %-12s %-9s \n", node->title, node->year, node->runningTime, node->genres, node->date, node->type);
    printUserLog(node->right);
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

void writeUserLog(Node* movie, char *username){
    char * filename = (char *) malloc(1 + strlen(username)+ strlen(".log"));
    strcpy(filename, username);
    strcat(filename, ".log");
    FILE *fp;
    fp = fopen(filename, "w"); // a+ (create + append) option will allow appending which is useful in a log file
    if (fp == NULL) {
        printf("Could not open file %s", filename);
    }
    fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s \n", "Title", "Year", "Runtime", "Genres", "Date", "Type");
    printFileInorder(fp, movie);
    //fprintf(fp,"%-25s %-6s %-7s %-30s %-12s %-9s \n", movie->primaryTitle, movie->year, movie->runtime, movie->genres, movie->date, movie->type);
    //fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\n", movie->title, movie->year, movie->runningTime, movie->genres, movie->date, movie->type);
    fclose(fp);
    //printf("\nTitle\t\t\tYear\tRuntime\tGenres\tDate\tType\t\n");
    //for (int i = 0; i < 10; i++){
        //if (movie->primaryTitle != NULL){
            //printLine(movie->primaryTitle, movie->year, movie->runtime, movie->genres, movie->date, movie->type);
        //}
    //}
}

void printLine(Node *movie){
    printf("%-25s\t%-6s\t%-7s\t%-30s\t%-12s\t%-9s\t\n", movie->title, movie->year, movie->runningTime, movie->genres, movie->date, movie->type);
}


