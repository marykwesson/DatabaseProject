//
// Created by bamam on 3/13/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "string.h"
#include "movie.h"

typedef struct Node{
    char *key;
    int id;
    struct Node *right;
    struct Node *left;
    int height;
}Node;

extern char *stringCompare(char *a, char *b);
extern int height(Node *n);
extern Node* newNode(char *title, int id);
extern Node* insert(Node* node, char *title, int id);
extern Node* searchTree(Node* root, char* title);
void printInorder(Node* node);
void printNode(Node* node);