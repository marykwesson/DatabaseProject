//
// Created by bamam on 3/15/2019.
//

#include "userLogs.h"

void createUserLog(char *username){
    char * filename = (char *) malloc(25);;
    strcpy(filename, username);
    strcat(filename, ".log");
    FILE *fp;
    fp = fopen(filename, "a+");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
    }
    fprintf(fp,"%-75s %-6s %-7s %-30s %-12s %-9s \n", "Title", "Year", "Runtime", "Genres", "Date", "Type");
    fclose(fp);
}

void readUserLog(char *username){
    char * filename = (char *) malloc(25);
    strcpy(filename, username);
    strcat(filename, ".log");
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
    }
    Node* userTree = NULL;
    userTree = readLogIntoTree(userTree, username);
    printf("%-75s %-6s %-7s %-30s %-12s %-9s \n", "Title", "Year", "Runtime", "Genres", "Date", "Type");
    printUserLog(userTree);
    fclose(fp);
}

void printUserLog(Node *node) {
    if (node == NULL) {
        return;
    }
    printUserLog(node->left);
    printf("%-75s %-6s %-7s %-30s %-12s %-9s \n", node->title, node->year, node->runningTime, node->genres, node->date, node->type);
    printUserLog(node->right);
}


void deleteUserLog(char *username){
    char * filename = (char *) malloc(25);
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
    char * filename = (char *) malloc(25);
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
    char * filename = (char *) malloc(25);
    strcpy(filename, username);
    strcat(filename, ".log");
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
    }
    fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s \n", "Title", "Year", "Runtime", "Genres", "Date", "Type");
    printFileInorder(fp, movie);
    fclose(fp);
}

void printLine(Node *node){
    printf("%-75s %-6s %-7s %-30s %-12s %-9s \n", node->title, node->year, node->runningTime, node->genres, node->date, node->type);
}


