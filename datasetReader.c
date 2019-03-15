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

char *strlower(char *str){
    unsigned char *tempstr = (unsigned char*)str;
    while(*tempstr){
        *tempstr = tolower(*tempstr);
        tempstr++;
    }
    return str;
}

int getIDNumber(char *titleId){
    int i = 2;
    int j = 9;
    char str[7];
    int IDNumber = 0;
    for(i = 2, j = 0; i < 9, j < 7; i++, j++){
        str[j] = titleId[i];
    }
    IDNumber = atoi(str);
    return IDNumber;
}

void articleChecker(char *str){
    const char *article[7];
    article[0] = "The ";
    article[1] = "A ";
    article[2] = "An ";
    article[3] = "De ";
    article[4] = "Los ";
    article[5] = "La ";
    article[6] = "El ";;
    for(int i = 0; i < 7; i++){
        strremove(str, article[i]);
    }
}

char *cleanString(char *original){
    char *new = strdup(original);
    articleChecker(new);
    new = strlower(new);
    return new;
}

Node *fileReader(char *filename){
    FILE *fp;
    char line[300];
    char *titleId = malloc(10);
    char *type = malloc(10);
    char *title = malloc(25);
    char *year = malloc(5);
    char *runtime = malloc(4);
    char *genres = malloc(5);
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

    while(fgets(line, 300, fp) != 0) {
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

        if (strcmp(type, "movie") == 0) {
            key = cleanString(title);
            IDNumber = getIDNumber(titleId);
            if (first == true){
                root = insert(root, key, IDNumber, title, genres, runtime, year);
                first = false;
            }
            else{
                insert(root, key, IDNumber, title, genres, runtime, year);
            }
        }
    }

    fclose(fp);
    return root;
}