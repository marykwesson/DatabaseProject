/**
 *
 *
 * Resources:
 * https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 */

#include "avl.h"

//A utility function to check if the title contains the search string
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

/*A function that allocates a new node using the given data
  and sets left and right pointers to NULL*/
Node *newNode(char *key, int id, char *title, char *genres, char *runningTime, char *year, char *date, char* type) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->key = malloc(sizeof(char)* (strlen(key) + 1));
    strcpy(node->key, key);
    node->id = id;
    node->title = malloc(sizeof(char)* (strlen(title) + 1));
    strcpy(node->title, title);
    node->genres = malloc(sizeof(char)* (strlen(genres) + 1));
    strcpy(node->genres, genres);
    node->runningTime = malloc(sizeof(char)* (strlen(runningTime) + 1));
    strcpy(node->runningTime, runningTime);
    node->year = malloc(sizeof(char)* (strlen(year) + 1));
    strcpy(node->year, year);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->date = malloc(sizeof(char)* (strlen(date) + 1));
    strcpy(node->date, date);
    node->type = malloc(sizeof(char)* (strlen(type) + 1));
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

//A function for the right right rotation case
Node *RR(Node *root) {
    Node *new = leftRotate(root);
    return new;
}

//A function for the left left rotation case
Node *LL(Node *root) {
    Node *new = rightRotate(root);
    return new;
}

//A function for the left right rotation case
Node *LR(Node *root) {
    root->left = leftRotate(root->left);
    Node *new = rightRotate(root);
    return new;
}

//A function for the right left rotation case
Node *RL(Node *root) {
    root->right = rightRotate(root->right);
    Node *new = rightRotate(root);
    return new;
}

//A Recursive function to insert a key into a tree and return the new root
//https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
Node *insert(Node *node, char *key, int id, char *title, char *genres, char *runningTime, char *year, char *date, char* type) {
    int balance;

    if (node == NULL) {
        return newNode(key, id, title, genres, runningTime, year, date, type);
    }

    if (strncmp(key, node->key, strlen(key)) < 0) {
        node->left = insert(node->left, key, id, title, genres, runningTime, year, date, type);
    } else if (strncmp(key, node->key, strlen(key)) >= 0) {
        node->right = insert(node->right, key, id, title, genres, runningTime, year, date, type);
    } else return node;

    balance = getBalance(node);

    //Left Left Case
    if (balance > 1 && strncmp(key, node->left->key, strlen(key)) < 0) {
        return LL(node);
    }

    //Right Right Case
    if (balance < -1 && strncmp(key, node->right->key, strlen(key)) > 0) {
        return RR(node);
    }

    //Left Right Case
    if (balance > 1 && strncmp(key, node->left->key, strlen(key)) > 0) {
        return LR(node);
    }

    //Right Left Case
    if (balance < -1 && strncmp(key, node->right->key, strlen(key)) < 0) {
        return RL(node);
    }
    return node;
}

//A function to return a tree of all results starting with the search term
Node *searchResults(Node *root, char *title, Node *results) {
    if (getCount(results) < 11) {
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
//https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
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

//A utiltiy function used to find the mimimum node in a search tree
Node* minimumValueNode(Node* node){
    Node *current = node;
    while (current->left != NULL){
        current = current->left;
    }
    return current;
}

//A recursive function used to delete a node from a tree
//https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
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

    //Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0){
        return LL(root);
    }

    //Left Right Case
    if (balance > 1 && getBalance(root->left) < 0){
        return LR(root);
    }

    //Right Right Case
    if (balance < -1 && getBalance(root->left) <= 0){
        return RR(root);
    }

    //Right Left Case
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

//A function used to print a tree to a file
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

//A recursive function used to put a tree into an array
int putInArray(Node *node, Node *array[], int index) {
    if (node == NULL) {
        return index;
    }
    if (node->left != NULL) {
        index = putInArray(node->left, array, index);
    }
    array[index] = newNode(node->key, index, node->title, node->genres, node->runningTime, node->year, node->date, node->type);
    index++;
    if (node->right != NULL) {
        index = putInArray(node->right, array, index);
    }
    return index;
}

//A recursive function to get the number of leaves in a tree
int getLeafCount(Node *node) {
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 1;
    else
        return getLeafCount(node->left) + getLeafCount(node->right);
}

//A recursive function used to get the number of nodes in a tree
int getCount(Node *root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + getCount(root->left) + getCount(root->right);
    }
}

//A function used to change the type of a node (movie)
void changeType(Node *movie, char typechoice){
    char *newType;
    if (typechoice == 'B' || typechoice == 'b'){
        newType = "Blu-ray";
    }
    if (typechoice == 'D' || typechoice == 'd'){
        newType = "DVD";
    }
    if (typechoice == 'G' || typechoice == 'g'){
        newType = "Digital";
    }
    movie->type = malloc(strlen(newType) +1);
    strncpy(movie->type, newType, 8);
}

//A function used to change the date of a node (movie)
void changeDate(Node *movie, char *newDate){
    movie->date = malloc(strlen(newDate) +1);
    strncpy(movie->date, newDate, 11);
}

//A function used to get the current date
char *getDate(){
    char buff[11];
    char *currentDate = malloc(sizeof(buff));
    time_t result = time(NULL);
    strftime(buff, sizeof(buff), "%m/%d/%Y", localtime(&result));
    return strncpy(currentDate, buff, 11);
}

void deleteTree(Node *root){
    if (root == NULL){
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    free(root->key);
    free(root->title);
    free(root->runningTime);
    free(root->year);
    free(root->date);
    free(root->type);
    free(root->genres);
    free(root);
}