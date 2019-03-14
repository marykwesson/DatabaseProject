/**
 *
 *
 * Resources:
 * https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 */

#include "avl.h"

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

Node* newNode(char* title, int id){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = strdup(title);
    node->id = id;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

Node* insert(Node* node, char *title, int id){
    if (node == NULL){
        return newNode(title, id);
    }

    if (strcmp(title,node->key) < 0){
        node->left = insert(node->left, title, id);
    }else if (strcmp(title,node->key) > 0){
        node->right = insert(node->right, title, id);
    }

    return node;
}


Node* searchTree(Node* root, char* title){
    if (root == NULL || strcmp(title,root->key) == 0){
        return root;
    }
    if (strcmp(title,root->key) > 0){
        return searchTree(root->right, title);
    }else if (strcmp(title,root->key) < 0){
        return searchTree(root->left, title);
    }
}

void printInorder(Node* node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->left);
    printf("%s\t\t\t%d\n", node->key, node->id);
    printInorder(node->right);
}

void printNode(Node *node){
    printf("%s\t\t\t%d\n", node->key, node->id);
}
