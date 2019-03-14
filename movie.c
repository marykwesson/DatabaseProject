//
// Created by bamam on 3/13/2019.
//

#include "movie.h"

Movie *newMovie(char *titleId, char *type, char *primaryTitle, char *year, char *runtime, char *genres) {
    struct Movie* movie = (struct Movie*)malloc(sizeof(struct Movie));
    movie->titleId = titleId;
    movie->type = type;
    movie->primaryTitle = primaryTitle;
    movie->year = year;
    movie->runtime = runtime;
    movie->genres = genres;
    return(movie);
}

void printMovie(Movie *movie){
    printf("ID: %s\nType: %s\nTitle: %s\nYear: %s\nRuntime: %s\nGenres: %s\n", movie->titleId, movie->type, movie->primaryTitle, movie->year, movie->runtime, movie->genres);
}

void printMovieSingleLine(Movie *movie){
    printf("%s\t%s\t%s\t%s\t%s\t%s", movie->titleId, movie->type, movie->primaryTitle, movie->year, movie->runtime, movie->genres);
}


