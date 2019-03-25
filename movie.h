//
// Created by bamam on 3/13/2019.
//
#ifndef MOVIE_H
#define MOVIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>


typedef struct Movie{
    int titleId;
    char *type;
    char *primaryTitle;
    char *year;
    char *runtime;
    char *genres;
    char *date;
} Movie;

extern Movie* newMovie(int titleId, char *primaryTitle, char *year, char *runtime, char *genres);
extern Movie *writeMovie(Movie *newMovie, Movie *oldMovie);
extern Movie *newBlankMovie();
extern void printMovie(Movie *movie);
extern void printMovieSingleLine(Movie *movie);
extern void changeType(Movie *movie, char *type);
extern void changeDate(Movie *movie, char *date);
extern char *getDate();


#endif