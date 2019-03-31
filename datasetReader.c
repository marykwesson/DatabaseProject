#include "datasetReader.h"

//A utiltiy function to remove a substring
char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

//https://stackoverflow.com/questions/23618316/undefined-reference-to-strlwr
//Implementation of non-standard function to write a string to lowercase
char *strlwr(char *str){
    unsigned char *p = (unsigned char *)str;
    while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
    }
    return str;
}

//Function to get the id number from the titleID
int getIDNumber(char *titleId){
    int i = 2;
    int j = 9;
    char str[7];
    int IDNumber = 0;
    for(i = 2, j = 0; i < 9 && j < 7; i++, j++){
        str[j] = titleId[i];
    }
    IDNumber = atoi(str);
    return IDNumber;
}

//Function to remove english articles
void articleChecker(char *str){
    const char *article[3];
    article[0] = "the ";
    article[1] = "a ";
    article[2] = "an ";
    for(int i = 0; i < 3; i++){
        strremove(str, article[i]);
    }
}

//Function to convert a string to lowercase with no articles
char *cleanString(char *original){
    strlwr(original);
    articleChecker(original);
    return original;
}

//Function for read the lookup dataset into memory
Node *fileReader(char *filename){
    FILE *fp;
    char line[400];
    char *titleId = malloc(sizeof(char)*10);
    char *type = malloc(sizeof(char)*10);
    type = "/0";
    char *title = malloc(sizeof(char)*256);
    char *year = malloc(sizeof(char)*5);
    char *runtime = malloc(sizeof(char)*4);
    char *genres = malloc(sizeof(char)*5);
    char *date = "/0";
    char *key;
    bool first = true;
    int IDNumber = 0;
    char delim[] = {"\t"};
    char *tok;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return NULL;
    }

    fgets(line, 300, fp);               //gets file header
    Node *root = NULL;

    while(fgets(line, 400, fp) != 0) {
        tok = strtok(line, delim);      //Gets  TitleId token
        if (tok) titleId = tok;
        tok = strtok(NULL, delim);      //Gets Type token
        if (tok) type = tok;
        tok = strtok(NULL, delim);      //Gets Title token
        if (tok) title = tok;
        tok = strtok(NULL, delim);      //Consume and ignore
        tok = strtok(NULL, delim);      //Consume and ignore
        tok = strtok(NULL, delim);      //Get Year token
        if (tok) year = tok;
        tok = strtok(NULL, delim);      //Consume and ignore
        tok = strtok(NULL, delim);      //Get Runtime token
        if (tok) runtime = tok;
        tok = strtok(NULL, delim);      //get GenresToken
        if (tok) genres = tok;
        genres[strcspn(genres, "\n")] = 0;

            char* newTitle = malloc(strlen(title));
            strncpy(newTitle,title, strlen(title));
            key = cleanString(title);
            IDNumber = getIDNumber(titleId);
            if (first == true){
                root = insert(root, key, IDNumber, newTitle, genres, runtime, year, date, type);
                first = false;
            }
            else{
                insert(root, key, IDNumber, newTitle, genres, runtime, year, date, type);
            }
    }

    fclose(fp);
    return root;
}

//Function to read the User Log file into Memory
Node* readLogIntoTree(Node* userTree, char *username) {
    char *filename = (char *) malloc(25);
    strcpy(filename, username);
    strcat(filename, ".log");
    FILE *fp;
    char *title = malloc(256);
    char *year = malloc(5);
    char *runtime = malloc(4);
    char *genres = malloc(5);
    char *date = malloc(11);
    char *type = malloc(8);
    char *key;
    bool first = true;
    int IDNumber = 0;
    char *titleId = "0";
    char line[300];
    char *tok;
    char delim[] = {"\t"};
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return NULL;
    }
    fgets(line, 300, fp);

    while (fgets(line, 300, fp) != 0) {
        tok = strtok(line, delim);      //Gets  titl token
        if (tok) title = tok;
        tok = strtok(NULL, delim);      //Gets year token
        if (tok) year = tok;
        tok = strtok(NULL, delim);      //Gets runtime token
        if (tok) runtime = tok;
        tok = strtok(NULL, delim);      //Get genres token
        if (tok) genres = tok;
        tok = strtok(NULL, delim);      //Get date token
        if (tok) date = tok;
        tok = strtok(NULL, delim);      //Get type token
        if (tok) type = tok;
        type[strcspn(type, "\n")] = 0;

        char *newTitle = malloc(strlen(title));
        strncpy(newTitle, title, strlen(title));
        key = cleanString(title);       
        IDNumber = getIDNumber(titleId);
        if (first) {
            userTree = insert(userTree, key, IDNumber, newTitle, genres, runtime, year, date, type);
            first = false;
        } else {
            insert(userTree, key, IDNumber, newTitle, genres, runtime, year, date, type);
        }
    }
    fclose(fp);
    return userTree;
}