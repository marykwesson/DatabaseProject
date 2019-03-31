//
// Created by bamam on 3/13/2019.
//
#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

typedef struct Node{
    char *key;
    int id;
    char *title;
    char *genres;
    char *runningTime;
    char *year;
    struct Node *right;
    struct Node *left;
    int height;
    char *date;
    char *type;
}Node;

extern bool stringContains(char *nodeTitle, char *searchString);
extern int height(Node *n);
extern int maxHeight(int height1, int height2);
extern int getBalance(Node *node);
extern Node* newNode(char *key, int id, char *title, char *genres, char *runningTime, char *year, char *date, char* type);
extern Node *rightRotate(Node *y);
extern Node *leftRotate(Node *x);
extern Node *RR(Node *root);
extern Node *LL(Node *root);
extern Node *LR(Node *root);
extern Node *RL(Node *root);
extern Node* insert(Node* node, char *key, int id, char *title, char *genres, char *runningTime, char *year, char *date, char* type);
extern Node *searchResults(Node *root, char *title, Node *results);
extern bool iterativeSearch(Node *root, char *title);
extern Node* searchTree(Node* root, char* title);
extern void printInorder(Node* node);
extern void printFileInorder(FILE *fp, Node *node);
extern void printPreorder(Node* node);
extern int putInArray(Node *node, Node *array[], int index);
extern int getLeafCount(Node* node);
extern int getCount(Node *tree);
extern Node* minimumValueNode(Node* node);
extern Node *deleteNode(Node* root, char *key);
extern void changeType(Node *movie, char newType);
extern void changeDate(Node *movie, char *newDate);
extern char *getDate();
extern void deleteTree(Node *root);
#endif