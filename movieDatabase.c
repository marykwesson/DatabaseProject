//
// Created by bamam on 3/13/2019.
//

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "movie.h"

#define MAX_FILE_NAME 100

int main(void)
{
    FILE *fp;
    char filename[MAX_FILE_NAME];
    char line[300];


    //printf("Enter file name: ");
    //scanf("%s", filename);
    strcpy(filename, "testdata.tsv");
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 0;
    }

    fgets(line, 300, fp);       //gets file header

    char delim[] = {"\t"};//parse using only newline and double quote
    char *tok;

    char *tempTitleId = malloc(10);
    char *tempType = malloc(10);
    char *tempTitle = malloc(25);
    char *tempYear = malloc(5);
    char *tempRuntime = malloc(4);
    char *tempGenres = malloc(5);

    printf("The data for your movie is:\n");
    while(fgets(line, 300, fp) != 0) {

        tok = strtok(line, delim);      //Gets  TitleId token
        if (tok) tempTitleId = tok;
        tok = strtok(NULL, delim);      //Gets Type token
        if (tok) tempType = tok;
        tok = strtok(NULL, delim);      //Gets Title token
        if (tok) tempTitle = tok;
        tok = strtok(NULL, delim);      //Consume and ignore
        tok = strtok(NULL, delim);      //Consume and ignore
        tok = strtok(NULL, delim);      //Get Year token
        if (tok) tempYear = tok;
        tok = strtok(NULL, delim);      //Consume and ignore
        tok = strtok(NULL, delim);      //Get Runtime token
        if (tok) tempRuntime = tok;
        tok = strtok(NULL, delim);      //get GenresToken
        if (tok) tempGenres = tok;

        if (strcmp(tempType, "movie") == 0){
            Movie *movie = newMovie(tempTitleId, tempType, tempTitle, tempYear, tempRuntime, tempGenres);
            printMovieSingleLine(movie);
            free(movie);
        }


    }
    fclose(fp);
    return 0;
}