/**
 *
 *
 * Resources:
 * https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 */

#include "avl.h"

//A utility function to check if the title contains the search string
/*int stringContains(char *nodeTitle, char *searchString){
    //printf("Search string is: %s", searchString);
    if(strncmp(nodeTitle, searchString, strlen(searchString)) == 0){
        return 0;
    }
    return 1;
}*/


bool stringContains(char *nodeTitle, char *searchString) {
    if (strncmp(nodeTitle, searchString, strlen(searchString)) == 0) {
        return false;
    }
    return true;
}

//A utility function to get the height of a node
int height(Node *n) {
    if (n == NULL) {
        return 0;
    } else {
        return n->height;
    }
}

//A utility function to get the maximum height of two nodes
int maxHeight(int height1, int height2) {
    return (height1 >= height2) ? height1 : height2;
}

//A utility function to get the balance factor
int getBalance(Node *node) {
    int balance = 0;
    if (node == NULL) {
        return 0;
    }
    balance = height(node->left) - height(node->right);
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
Node *newNode(char *key, int id, char *title, char *genres, char *runningTime, char *year, char *date, char* type) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->key = malloc(strlen(key) + 1);
    strcpy(node->key, key);
    node->id = id;
    node->title = malloc(strlen(title) + 1);
    strcpy(node->title, title);
    node->genres = malloc(strlen(genres) + 1);
    strcpy(node->genres, genres);
    node->runningTime = malloc(strlen(runningTime) + 1);
    strcpy(node->runningTime, runningTime);
    node->year = malloc(strlen(year) + 1);
    strcpy(node->year, year);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->date = malloc(strlen(date) + 1);
    strcpy(node->date, date);
    node->type = malloc(strlen(type) + 1);
    strcpy(node->type, type);
    return (node);
}

//A function that rotates a given node to the right
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *z = x->right;

    x->right = y;
    y->left = z;

    y->height = maxHeight(height(y->left), height(y->right)) + 1;
    x->height = maxHeight(height(x->left), height(x->right)) + 1;

    return x;
}

//A function that rotates a given node to the left
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *z = y->left;

    y->left = x;
    x->right = z;

    x->height = maxHeight(height(x->left), height(x->right)) + 1;
    y->height = maxHeight(height(y->left), height(y->right)) + 1;

    return y;
}

//A function for the right right case
Node *RR(Node *root) {
    Node *new = leftRotate(root);
    return new;
}

//A function for the left left case
Node *LL(Node *root) {
    Node *new = rightRotate(root);
    return new;
}

//A function for the left right case
Node *LR(Node *root) {
    root->left = leftRotate(root->left);
    Node *new = rightRotate(root);
    return new;
}

//A function for the right left case
Node *RL(Node *root) {
    root->right = rightRotate(root->right);
    Node *new = rightRotate(root);
    return new;
}

//A Recursive function to insert a key into a tree and return the new root
Node *insert(Node *node, char *key, int id, char *title, char *genres, char *runningTime, char *year, char *date, char* type) {
    int balance;

    if (node == NULL) {
        return newNode(key, id, title, genres, runningTime, year, date, type);
    }

    if (strcmp(key, node->key) < 0) {
        node->left = insert(node->left, key, id, title, genres, runningTime, year, date, type);
    } else if (strcmp(key, node->key) >= 0) {
        node->right = insert(node->right, key, id, title, genres, runningTime, year, date, type);
    } else return node;

    balance = getBalance(node);

    if (balance > 1 && strcmp(key, node->left->key) < 0) {
        return LL(node);
    }

    if (balance < -1 && strcmp(key, node->right->key) > 0) {
        return RR(node);
    }

    if (balance > 1 && strcmp(key, node->left->key) > 0) {
        return LR(node);
    }

    if (balance < -1 && strcmp(key, node->right->key) < 0) {
        return RL(node);
    }
    return node;
}

//A recursive function to search for every instance of a search term
/*Node *searchResults(Node *root, char *title, Node *results) {
    Node *searchTerm = searchTree(root, title);
    if (searchTerm != NULL) {
        if (results == NULL) {
            results = insert(results, searchTerm->key, searchTerm->id, searchTerm->title, searchTerm->genres,
                             searchTerm->runningTime, searchTerm->year);
        } else {
            insert(results, searchTerm->key, searchTerm->id, searchTerm->title, searchTerm->genres,
                   searchTerm->runningTime, searchTerm->year);
        }

        if (iterativeSearch(searchTerm->left, title) == true && iterativeSearch(searchTerm->right, title) == true) {
            results = searchResults(searchTerm->left, title, results);
            return searchResults(searchTerm->right, title, results);
        } else if (iterativeSearch(searchTerm->left, title) == true) {
            return searchResults(searchTerm->left, title, results);
        } else if (iterativeSearch(searchTerm->right, title) == true) {
            return searchResults(searchTerm->right, title, results);
        }
    }
    return results;
}*/




Node *searchResults(Node *root, char *title, Node *results) {
    if (getCount(results) < 11) {
        //printf("Count = %d", count);
        Node *searchTerm = searchTree(root, title);
        if (searchTerm != NULL) {
            if (results == NULL) {
                results = insert(results, searchTerm->key, searchTerm->id, searchTerm->title, searchTerm->genres,
                                 searchTerm->runningTime, searchTerm->year, searchTerm->date, searchTerm->type);
            } else {
                insert(results, searchTerm->key, searchTerm->id, searchTerm->title, searchTerm->genres,
                       searchTerm->runningTime, searchTerm->year, searchTerm->date, searchTerm->type);
            }

            if (iterativeSearch(searchTerm->left, title) == true && iterativeSearch(searchTerm->right, title) == true) {
                results = searchResults(searchTerm->left, title, results);
                return searchResults(searchTerm->right, title, results);
            } else if (iterativeSearch(searchTerm->left, title) == true) {
                return searchResults(searchTerm->left, title, results);
            } else if (iterativeSearch(searchTerm->right, title) == true) {
                return searchResults(searchTerm->right, title, results);
            }
        }
    }
    return results;
}

//A boolean function that checks if the search term is present
bool iterativeSearch(Node *root, char *title) {
    if (root == NULL) {
        return false;
    }
    if (!stringContains(root->key, title)) {
        return true;
    }
    if (strncmp(title, root->key, strlen(title)) > 0) {
        return iterativeSearch(root->right, title);
    } else if (strncmp(title, root->key, strlen(title)) < 0) {
        return iterativeSearch(root->left, title);
    }
    return false;
}

/*A recursive function that searches for an instance of a node
  and returns the node if it is present*/
/*Node* searchTree(Node* root, char* title){
    if (root == NULL){
        return root;
    }
    *//*if (!stringContains(root->key, title)){
        return root;
    }*//*
    if (strncmp(title,root->key,strlen(title)) == 0){
        return root;
    }
    if (strcmp(title,root->key) > 0){
        return searchTree(root->right, title);
    }else if (strcmp(title,root->key) < 0){
        return searchTree(root->left, title);
    }
    return NULL;
}*/
Node *searchTree(Node *root, char *title) {
    if (root == NULL || !stringContains(root->key, title)) {
        return root;
    }
    if (strncmp(title, root->key, strlen(title)) > 0) {
        return searchTree(root->right, title);
    } else if (strncmp(title, root->key, strlen(title)) < 0) {
        return searchTree(root->left, title);
    }
    return NULL;
}

Node* minimumValueNode(Node* node){
    Node *current = node;
    while (current->left != NULL){
        current = current->left;
    }
    return current;
}

Node *deleteNode(Node* root, char *key){
    if(root == NULL){
        return root;
    }
    if(strncmp(key, root->key, strlen(key)) < 0){
        root->left = deleteNode(root->left, key);
    }
    else if(strncmp(key, root->key, strlen(key)) > 0){
        root->right = deleteNode(root->right, key);
    }
    else{
        if (root->left == NULL || root->right == NULL){
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL){
                temp = root;
                root = NULL;
            }
            else{
                *root = *temp;
                free(temp);
            }
        }
        else{
            Node *temp = minimumValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (root == NULL){
        return root;
    }
    root->height = 1 + maxHeight(height(root->left),height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0){
        return LL(root);
    }
    if (balance > 1 && getBalance(root->left) < 0){
        return LR(root);
    }
    if (balance < -1 && getBalance(root->left) <= 0){
        return RR(root);
    }
    if (balance < -1 && getBalance(root->left) > 0){
        return RL(root);
    }
    return root;
}

//A recursive function to print an inorder traversal of a tree
void printInorder(Node *node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->left);
    printf("%s (%s)\n", node->key, node->year);
    printInorder(node->right);
}

void printFileInorder(FILE *fp, Node *movie) {
    if (movie == NULL) {
        return;
    }
    printFileInorder(fp, movie->left);
    fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\n", movie->title, movie->year, movie->runningTime, movie->genres, movie->date, movie->type);
    printFileInorder(fp, movie->right);
}

//A recursive function to print an preorder traversal of a tree
void printPreorder(Node *node) {
    if (node == NULL) {
        return;
    }
    printf("%s (%s)\n", node->key, node->year);
    printPreorder(node->left);
    printPreorder(node->right);
}

int putInArray(Node *node, Node *array[], int index) {
    if (node == NULL) {
        return index;
    }
    if (node->left != NULL) {
        index = putInArray(node->left, array, index);
    }
    //array[index] = newMovie(index, node->title, node->year, node->runningTime, node->genres);
    array[index] = newNode(node->key, index, node->title, node->genres, node->runningTime, node->year, node->date, node->type);
    index++;
    if (node->right != NULL) {
        index = putInArray(node->right, array, index);
    }
    return index;
}


int getLeafCount(Node *node) {
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 1;
    else
        return getLeafCount(node->left) + getLeafCount(node->right);
}

int getCount(Node *root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + getCount(root->left) + getCount(root->right);
    }
}

void changeType(Node *movie, char *newType){
    movie->type = malloc(strlen(newType) +1);
    strcpy(movie->type, newType);
}

void changeDate(Node *movie, char *newDate){
    movie->date = malloc(strlen(newDate) +1);
    strcpy(movie->date, newDate);
}