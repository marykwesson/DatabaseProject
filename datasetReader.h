//
// Created by bamam on 3/13/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "string.h"

struct Movie{
    char *titleId;
    char *type;
    char *primaryTitle;
    char *originalTitle;
    bool adult;
    char StartYear[4];
    char EndYear[4];
    int runtime;
    char *genres;
};


