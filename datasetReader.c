#include "datasetReader.h"

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

char *strlwr(char *str)
{
    unsigned char *p = (unsigned char *)str;

    while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
    }

    return str;
}

char *strlower(char *str){
    char *tempstr = str;
    while(*tempstr){
        *tempstr = (char) tolower(*tempstr);
        tempstr++;
    }
    return str;
}

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

void articleChecker(char *str){
    const char *article[3];
    article[0] = "the ";
    article[1] = "a ";
    article[2] = "an ";
    //article[3] = "the ";
    //article[4] = "a ";
    //article[5] = "an ";
    //article[6] = "El ";
    for(int i = 0; i < 3; i++){
        strremove(str, article[i]);
    }
}

char *cleanString(char *original){
    //printf("Made it into clean string");
    //char *new = malloc(strlen(original) +1);
    //strcpy(new, original);
    strlwr(original);
    articleChecker(original);
    //new = strlower(new);
    return original;
}

void cleanInput(char *original){
    //printf("Made it into clean string");
    //char *new = malloc(strlen(original) +1);
    //strcpy(new, original);
    articleChecker(original);
    strlwr(original);
    //new = strlower(new);
}

Node *fileReader(char *filename){
    FILE *fp;
    char line[400];
    char *titleId = malloc(10);
    char *type = malloc(10);
    type = "/0";
    char *title = malloc(256);
    char *year = malloc(5);
    char *runtime = malloc(4);
    char *genres = malloc(5);
    char *date = "/0";
    char *key;
    bool first = true;
    int IDNumber = 0;
    char delim[] = {"\t"};//parse using only newline and double quote
    char *tok;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 0;
    }

    fgets(line, 300, fp);       //gets file header
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

        //if (strcmp(type, "movie") == 0) {
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
        //}
    }
    //free(line);

    fclose(fp);
    return root;
}


Node *readLogIntoTree(char *username) {
    char *filename = (char *) malloc(1 + strlen(username) + strlen(".log"));
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
        return 0;
    }
    fgets(line, 300, fp);
    Node *root = NULL;

    while (fgets(line, 300, fp) != 0) {
        tok = strtok(line, delim);      //Gets  TitleId token
        if (tok) title = tok;
        tok = strtok(NULL, delim);      //Gets Type token
        if (tok) year = tok;
        tok = strtok(NULL, delim);      //Gets Title token
        if (tok) runtime = tok;
        tok = strtok(NULL, delim);      //Get Year token
        if (tok) genres = tok;
        tok = strtok(NULL, delim);      //Consume and ignore
        if (tok) date = tok;
        tok = strtok(NULL, delim);      //get GenresToken
        if (tok) type = tok;
        type[strcspn(type, "\n")] = 0;

        char *newTitle = malloc(strlen(title));
        strncpy(newTitle, title, strlen(title));
        key = cleanString(title);
        IDNumber = getIDNumber(titleId);
        if (first) {
            root = insert(root, key, IDNumber, newTitle, genres, runtime, year, date, type);
            first = false;
        } else {
            insert(root, key, IDNumber, newTitle, genres, runtime, year, date, type);
        }
    }
    fclose(fp);
    return root;
}