//
// Created by bamam on 3/13/2019.
//

#include "datasetReader.h"

struct Movie* newMovie(){
    struct Movie* movie = (struct Movie*)malloc(sizeof(struct Movie));
    movie->titleId = NULL;
    movie->type = NULL;
    movie->primaryTitle = NULL;
    movie->originalTitle = NULL;
    movie->adult = 0;
    movie->StartYear[4] = "YYYY";
    movie->EndYear[4] = "YYYY";
    movie->runtime = 0
    movie->genres = NULL;
    return(movie);
}



