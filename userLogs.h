//
// Created by bamam on 3/15/2019.
//
#ifndef USERLOGS_H
#define USERLOGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "movie.h"

extern void createUserLog(char *username);
extern int exists(char *fileName);
extern void readUserLog(char *filename);
extern void deleteUserLog(char *username);
extern void writeUserLog(Movie* movie, char *username);
extern void printLine(Movie *movie);

#endif