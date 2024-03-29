#ifndef DATASETREADER_H
#define DATASETREADER_H

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "avl.h"

extern char *strremove(char *str, const char *sub);
extern char *strlower(char *str);
extern int getIDNumber(char *titleId);
extern void articleChecker(char *str);
extern char *cleanString(char *original);
extern Node *fileReader(char *filename);
extern void cleanInput(char *original);
extern Node* readLogIntoTree(Node* userTree, char *username);
#endif