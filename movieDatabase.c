//
// Created by bamam on 3/13/2019.
//

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "movie.h"

#define MAX_FILE_NAME 100

//struct Movie{
//    char titleId[10];
//    char type[10];
//    char primaryTitle[25];
//    char year[5];
//    char runtime[4];
//    char genres[40];
//};
//
//struct Movie{
//    char *titleId;
//    char *type;
//    char *primaryTitle;
//    char *Year;
//    char *runtime;
//    char *genres;
//};

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

    fgets(line, 300, fp);
    printf("The first line is:\n%s\n", line);

    char delim[] = {"\t"};//parse using only newline and double quote
    char *tok;

    char *tempTitleId = malloc(10);
    char *tempType = malloc(10);
    char *tempTitle = malloc(25);
    char *tempYear = malloc(5);
    char *tempRuntime = malloc(4);
    char *tempGenres = malloc(5);

    fgets(line, 300, fp);

    tok = strtok(line, delim);      //Gets  TitleId token
    if(tok) tempTitleId = tok;
    tok = strtok(NULL, delim);      //Gets Type token
    if(tok) tempType = tok;
    tok = strtok(NULL, delim);      //Gets Title token
    if(tok) tempTitle = tok;
    tok = strtok(NULL, delim);      //Consume and ignore
    tok = strtok(NULL, delim);      //Consume and ignore
    tok = strtok(NULL, delim);      //Get Year token
    if(tok) tempYear = tok;
    tok = strtok(NULL, delim);      //Consume and ignore
    tok = strtok(NULL, delim);      //Get Runtime token
    if(tok) tempRuntime = tok;
    tok = strtok(NULL, delim);      //get GenresToken
    if(tok) tempGenres = tok;


    Movie *movie = newMovie(tempTitleId, tempType, tempTitle, tempYear, tempRuntime, tempGenres);
    printf("The data for your movie is:\n");
    printMovie(movie);

//    struct Movie* movie = (struct Movie*)malloc(sizeof(struct Movie));
//    strcpy(movie->titleId, tempTitleId);
//    strcpy(movie->type, tempType);
//    strcpy(movie->primaryTitle, tempTitle);
//    strcpy(movie->year, tempYear);
//    strcpy(movie->runtime, tempRuntime);
//    strcpy(movie->genres, tempGenres);

    //printf("the titleid is: %s\n the length is: %lu\n", movie->titleId, strlen(movie->titleId));
    //printf("ID: %s\n Type: %s\n Title: %s\n Year: %s\n Runtime: %s\n Genres: %s\n", movie->titleId, movie->type, movie->primaryTitle, movie->year, movie->runtime, movie->genres);



//    sscanf(line, "%s\t\t%s\t%s\t%*s\t%*d\t%s\t%*s\t%s\t%s", &movie->titleId, movie->type, movie->primaryTitle, movie->Year, movie->runtime, movie->genres);
//    //sscanf(line, "%s\t%s\t%s\t\t\t%s\t\t%d\t%s", movie->titleId, movie->type, movie->primaryTitle, movie->Year, &movie->runtime, movie->genres);
//    printf("the titleid is: %s\n the length is: %lu\n", &movie->titleId, strlen(movie->titleId));
//    printf("ID: %s\n Type: %s\n Title: %s\n Year: %s\n Runtime: %s\n Genres: %s\n", movie->titleId, movie->type, movie->primaryTitle, movie->Year, &movie->runtime, movie->genres);
//    printf("The second line is:\n%s\n", line);


    fclose(fp);
    return 0;
}