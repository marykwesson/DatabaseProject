//
// Created by bamam on 3/15/2019.
//
#ifndef USERLOGS_H
#define USERLOGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"
#include "datasetReader.h"

extern void createUserLog(char *username);
extern int exists(char *fileName);
extern void readUserLog(char *filename);
extern void deleteUserLog(char *username);
extern void writeUserLog(Node* movie, char *username);
extern void printLine(Node *movie);
extern void printUserLog(Node *node);

#endif