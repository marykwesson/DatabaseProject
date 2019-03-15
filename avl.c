/**
 *
 *
 * Resources:
 * https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 */

#include "avl.h"

bool stringContains(char *nodeTitle, char *searchString){
    if(strncmp(nodeTitle, searchString, strlen(searchString)) == 0){
        return false;
    }
    return true;
//    if (strstr(nodeTitle, searchString) != NULL){
//        return true;
//    }
//    else{
//        return false;
//    }
}


int height(Node *n){
    if (n == NULL) {
        return 0;
    }else{
        return n->height;
    }
}

int maxHeight(int height1, int height2){
    return (height1 >= height2)? height1 : height2;
}

int getBalance(Node *node){
    int balance = 0;
    if(node == NULL){
        return 0;
    }
    balance = height(node->left)-height(node->right);
    return balance;
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

//Node* insert(Node* node, char *title, int id){
//    if (node == NULL){
//        return newNode(title, id);
//    }
//
//    if (strcmp(title,node->key) < 0){
//        node->left = insert(node->left, title, id);
//    }else if (strcmp(title,node->key) > 0){
//        node->right = insert(node->right, title, id);
//    }
//
//    return node;
//}

Node *rightRotate(Node *y){
    Node *x = y->left;
    Node *z = x->right;

    x->right = y;
    y->left = z;

    y->height = maxHeight(height(y->left), height(y->right))+1;
    x->height = maxHeight(height(x->left), height(x->right))+1;

    return x;
}

Node *leftRotate(Node *x){
    Node *y = x->right;
    Node *z = y->left;

    y->left = x;
    x->right = z;

    x->height = maxHeight(height(x->left), height(x->right))+1;
    y->height = maxHeight(height(y->left), height(y->right))+1;

    return y;
}

Node *RR(Node *root){
    Node *new = leftRotate(root);
    return new;
}

Node *LL(Node *root){
    Node *new = rightRotate(root);
    return new;
}

Node *LR(Node *root){
    root->left = leftRotate(root->left);
    Node *new = rightRotate(root);
    return new;
}

Node *RL(Node *root){
    root->right = rightRotate(root->right);
    Node *new = rightRotate(root);
    return new;
}



Node *insert(Node *node, char *title, int id){
    int balance;

    if (node == NULL){
        return newNode(title, id);
    }

    if (strcmp(title,node->key) < 0){
        node->left = insert(node->left, title, id);
    }else if (strcmp(title,node->key) >= 0){
        node->right = insert(node->right, title, id);
    }
    else return node;

    balance = getBalance(node);

    if (balance > 1 && strcmp(title,node->left->key) < 0){
        return LL(node);
    }

    if (balance < -1 && strcmp(title,node->right->key) > 0){
        return RR(node);
    }

    if (balance > 1 && strcmp(title,node->left->key) > 0){
        return LR(node);
    }

    if (balance < -1 && strcmp(title,node->right->key) < 0){
        return RL(node);
    }
    return node;
}

Node *searchResults(Node *root, char *title, int id, Node *results) {
    Node *searchTerm = searchTree(root, title);
    if (searchTerm != NULL) {
        if (results == NULL) {
            results = insert(results, searchTerm->key, searchTerm->id);
        } else {
            insert(results, searchTerm->key, searchTerm->id);
        }
    }
    if (iterativeSearch(searchTerm->left, title) == true && iterativeSearch(searchTerm->right, title) == true) {
        results = searchResults(searchTerm->left, title, id, results);
        return searchResults(searchTerm->right, title, id, results);
    } else if (iterativeSearch(searchTerm->left, title) == true) {
        return searchResults(searchTerm->left, title, id, results);
    } else if (iterativeSearch(searchTerm->right, title) == true) {
        return searchResults(searchTerm->right, title, id, results);
    }
    return results;
}

bool iterativeSearch(Node *root, char *title){
    if (root == NULL){
        return false;
    }
    if (!stringContains(root->key, title)){
        return true;
    }
    if (strcmp(title,root->key) > 0){
        return iterativeSearch(root->right, title);
    }else if (strcmp(title,root->key) < 0) {
        return iterativeSearch(root->left, title);
    }
//    while (root != NULL){
//        if (!stringContains(root->key, title)){
//            return true;
//        }
//        // pass right subtree as new tree
//        else if (strcmp(title,root->key) > 0)
//            root = root->right;
//
//            // pass left subtree as new tree
//        else if (strcmp(title,root->key) < 0)
//            root = root->left;
//    }
//    return false;
}

Node* searchTree(Node* root, char* title){
//    if (root == NULL || !stringContains(root->key, title)){
//        return root;
//    }
    if (root == NULL){
        return NULL;
    }
    if (!stringContains(root->key, title)){
        //printf("%s\t%d\n", root->key, root->id);
        return root;
    }
    if (strcmp(title,root->key) > 0){
        return searchTree(root->right, title);
    }else if (strcmp(title,root->key) < 0){
        return searchTree(root->left, title);
    }
}

//Node* searchTree(Node* root, char* title){
//    if (root == NULL || strcmp(title,root->key) == 0){
//        return root;
//    }
//    if (strcmp(title,root->key) > 0){
//        return searchTree(root->right, title);
//    }else if (strcmp(title,root->key) < 0){
//        return searchTree(root->left, title);
//    }
//}

void printInorder(Node* node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->left);
    printf("%s\t\t\t%d\n", node->key, node->id);
    printInorder(node->right);
}

void printPreorder(Node* node)
{
    if (node == NULL)
        return;

    printf("%s\t%d\n", node->key, node->id);
    printPreorder(node->left);
    printPreorder(node->right);
}

void printNode(Node *node){
    printf("%s\t\t\t%d\n", node->key, node->id);
}
