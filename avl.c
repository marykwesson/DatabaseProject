/**
 *
 *
 * Resources:
 * https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 */

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "string.h"

struct Node{
    char *title;
    int titleID;
    struct Node *right;
    struct Node *left;
    int height;
};

char *stringCompare(char *a, char *b){
    if (strcmp(a,b) < 0){
        return a;
    }else{
        return b;
    }
}

int height(struct Node *n){
    if (n == NULL) {
        return 0;
    }else{
        return n->height;
    }
}

struct Node* newNode(char *title, int titleID){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->title = title;
    node->titleID = titleID;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

struct Node* insert(struct Node* node, char *title, int titleID){
    if (node == NULL){
        return newNode(title, titleID);
    }

    if (strcmp(title,node->title) < 0){
        node->left = insert(node->left, title, titleID);
    }else if (strcmp(title,node->title) > 0){
        node->right = insert(node->right, title, titleID);
    }

    return node;
}

void printInorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->left);
    printf("%s %d\n", node->title, node->titleID);
    printInorder(node->right);
}

int main(){
    struct Node *root = NULL;
    char *str = "hannah!";
    root = insert(root, "elephant", 5);
    insert(root, "cat", 9);
    insert(root, "balloon", 8);
    insert(root, "dinosaur", 6);
    insert(root, "goat", 3);
    insert(root, "fox", 4);
    insert(root, "hannah", 14);
    insert(root, str, 15);
    insert(root, "dummy", 16);

    printInorder(root);
    return 0;

}