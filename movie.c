//
// Created by bamam on 3/13/2019.
//

#include "movie.h"

Movie *newMovie(int titleId, char *primaryTitle, char *year, char *runtime, char *genres) {
    char *currentDate = getDate();
    Movie* movie = (struct Movie*)malloc(sizeof(struct Movie));
    movie->titleId = titleId;
    movie->primaryTitle = primaryTitle;
    movie->year = year;
    movie->runtime = runtime;
    movie->genres = genres;
    movie->type = NULL;
    movie->date = currentDate;
    return(movie);
}

Movie *newBlankMovie() {
    Movie* movie = (struct Movie*)malloc(sizeof(struct Movie));
    movie->titleId = 0;
    movie->primaryTitle = NULL;
    movie->year = NULL;
    movie->runtime = NULL;
    movie->genres = NULL;
    movie->type = NULL;
    movie->date = NULL;
    return(movie);
}


Movie *writeMovie(Movie *newMovie, Movie *oldMovie){
    //Movie* movie = (struct Movie*)malloc(sizeof(struct Movie));
    newMovie->titleId = oldMovie->titleId;
    newMovie->type = oldMovie->type;
    newMovie->primaryTitle = oldMovie->primaryTitle;
    newMovie->year = oldMovie->year;
    newMovie->runtime = oldMovie->runtime;
    newMovie->genres = oldMovie->genres;
    return(newMovie);
}

void printMovie(Movie *movie){
    printf("ID: %d\nDate: %s\nTitle: %s\nYear: %s\nRuntime: %s\nGenres: %s\n", movie->titleId, movie->date, movie->primaryTitle, movie->year, movie->runtime, movie->genres);
}

void printMovieSingleLine(Movie *movie){
    printf("\n%s\t%s\t%s\t%s\t%s", movie->primaryTitle, movie->year, movie->runtime, movie->genres, movie->date);
}

void changeType(Movie *movie, char *newType){
    movie->type = malloc(strlen(newType) +1);
    strcpy(movie->type, newType);
}

void changeDate(Movie *movie, char *newDate){
    movie->date = malloc(strlen(newDate) +1);
    strcpy(movie->date, newDate);
}

char *getDate(){
    char buff[11];
    char *currentDate = malloc(sizeof(buff));
    time_t result = time(NULL);
    strftime(buff, sizeof(buff), "%m/%d/%Y", localtime(&result));
    //puts(buff);
    return strcpy(currentDate, buff);
}

