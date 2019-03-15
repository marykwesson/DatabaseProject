/**
 *
 *
 * Resources:
 * https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 */

#include "avl.h"

//A utility function to check if the title contains the search string
bool stringContains(char *nodeTitle, char *searchString){
    if(strncmp(nodeTitle, searchString, strlen(searchString)) == 0){
        return false;
    }
    return true;
}

//A utility function to get the height of a node
int height(Node *n){
    if (n == NULL) {
        return 0;
    }else{
        return n->height;
    }
}

//A utility function to get the maximum height of two nodes
int maxHeight(int height1, int height2){
    return (height1 >= height2)? height1 : height2;
}

//A utility function to get the balance factor
int getBalance(Node *node){
    int balance = 0;
    if(node == NULL){
        return 0;
    }
    balance = height(node->left)-height(node->right);
    return balance;
}

//Node* newNode(char* title, int id){
//    Node* node = (Node*)malloc(sizeof(Node));
//    node->key = strdup(title);
//    node->id = id;
//    node->left = NULL;
//    node->right = NULL;
//    node->height = 1;
//    return(node);
//}
/*A function that allocates a new node using the given data
  and sets left and right pointers to NULL*/
Node* newNode(char *key, int id, char *title, char *genres, char *runningTime, char *year){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = strdup(key);
    node->id = id;
    node->title = strdup(title);
    node->genres = strdup(genres);
    node->runningTime = strdup(runningTime);
    node->year = strdup(year);
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

//A function that rotates a given node to the right
Node *rightRotate(Node *y){
    Node *x = y->left;
    Node *z = x->right;

    x->right = y;
    y->left = z;

    y->height = maxHeight(height(y->left), height(y->right))+1;
    x->height = maxHeight(height(x->left), height(x->right))+1;

    return x;
}

//A function that rotates a given node to the left
Node *leftRotate(Node *x){
    Node *y = x->right;
    Node *z = y->left;

    y->left = x;
    x->right = z;

    x->height = maxHeight(height(x->left), height(x->right))+1;
    y->height = maxHeight(height(y->left), height(y->right))+1;

    return y;
}

//A function for the right right case
Node *RR(Node *root){
    Node *new = leftRotate(root);
    return new;
}

//A function for the left left case
Node *LL(Node *root){
    Node *new = rightRotate(root);
    return new;
}

//A function for the left right case
Node *LR(Node *root){
    root->left = leftRotate(root->left);
    Node *new = rightRotate(root);
    return new;
}

//A function for the right left case
Node *RL(Node *root){
    root->right = rightRotate(root->right);
    Node *new = rightRotate(root);
    return new;
}


//Node *insert(Node *node, char *title, int id){
//    int balance;
//
//    if (node == NULL){
//        return newNode(title, id);
//    }
//
//    if (strcmp(title,node->key) < 0){
//        node->left = insert(node->left, title, id);
//    }else if (strcmp(title,node->key) >= 0){
//        node->right = insert(node->right, title, id);
//    }
//    else return node;
//
//    balance = getBalance(node);
//
//    if (balance > 1 && strcmp(title,node->left->key) < 0){
//        return LL(node);
//    }
//
//    if (balance < -1 && strcmp(title,node->right->key) > 0){
//        return RR(node);
//    }
//
//    if (balance > 1 && strcmp(title,node->left->key) > 0){
//        return LR(node);
//    }
//
//    if (balance < -1 && strcmp(title,node->right->key) < 0){
//        return RL(node);
//    }
//    return node;
//}

//A Recursive function to insert a key into a tree and return the new root
Node* insert(Node* node, char *key, int id, char *title, char *genres, char *runningTime, char *year){
    int balance;

    if (node == NULL){
        return newNode(key, id, title, genres, runningTime, year);
    }

    if (strcmp(key,node->key) < 0){
        node->left = insert(node->left, key, id, title, genres, runningTime, year);
    }else if (strcmp(key,node->key) >= 0){
        node->right = insert(node->right, key, id, title, genres, runningTime, year);
    }
    else return node;

    balance = getBalance(node);

    if (balance > 1 && strcmp(key,node->left->key) < 0){
        return LL(node);
    }

    if (balance < -1 && strcmp(key,node->right->key) > 0){
        return RR(node);
    }

    if (balance > 1 && strcmp(key,node->left->key) > 0){
        return LR(node);
    }

    if (balance < -1 && strcmp(key,node->right->key) < 0){
        return RL(node);
    }
    return node;
}

//A recursive function to search for every instance of a search term
Node *searchResults(Node *root, char *title, Node *results) {
    Node *searchTerm = searchTree(root, title);
    if (searchTerm != NULL) {
        if (results == NULL) {
            results = insert(results, searchTerm->key, searchTerm->id, searchTerm->title, searchTerm->genres, searchTerm->runningTime, searchTerm->year);
        } else {
            insert(results, searchTerm->key, searchTerm->id, searchTerm->title, searchTerm->genres, searchTerm->runningTime, searchTerm->year);
        }
    }
    if (iterativeSearch(searchTerm->left, title) == true && iterativeSearch(searchTerm->right, title) == true) {
        results = searchResults(searchTerm->left, title, results);
        return searchResults(searchTerm->right, title, results);
    } else if (iterativeSearch(searchTerm->left, title) == true) {
        return searchResults(searchTerm->left, title, results);
    } else if (iterativeSearch(searchTerm->right, title) == true) {
        return searchResults(searchTerm->right, title, results);
    }
    return results;
}

//A boolean function that checks if the search term is present
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
}

/*A recursive function that searches for an instance of a node
  and returns the node if it is present*/
Node* searchTree(Node* root, char* title){
    if (root == NULL){
        return NULL;
    }
    if (!stringContains(root->key, title)){
        return root;
    }
    if (strcmp(title,root->key) > 0){
        return searchTree(root->right, title);
    }else if (strcmp(title,root->key) < 0){
        return searchTree(root->left, title);
    }
}

//A recursive function to print an inorder traversal of a tree
void printInorder(Node* node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->left);
    printf("%s (%s)\n", node->key, node->year);
    printInorder(node->right);
}

//A recursive function to print an preorder traversal of a tree
void printPreorder(Node* node){
    if (node == NULL) {
        return;
    }
    printf("%s (%s)\n", node->key, node->year);
    printPreorder(node->left);
    printPreorder(node->right);
}

