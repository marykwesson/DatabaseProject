//
// Created by bamam on 3/13/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "string.h"

typedef struct Movie{
    char *titleId;
    char *type;
    char *primaryTitle;
    char *year;
    char *runtime;
    char *genres;
} Movie;

extern Movie* newMovie(char *titleId, char *type, char *primaryTitle, char *year, char *runtime, char *genres);

extern void printMovie(Movie *movie);
