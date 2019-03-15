//
// Created by bamam on 3/13/2019.
//

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
//#include "movie.h"
#include "avl.h"

#define MAX_FILE_NAME 100

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

int main(void)
{
    FILE *fp;
    char filename[MAX_FILE_NAME];
    char line[300];


    //printf("Enter file name: ");
    //scanf("%s", filename);
    strcpy(filename, "testdata.tsv");
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 0;
    }

    fgets(line, 300, fp);       //gets file header

    Node *root = NULL;

    char delim[] = {"\t"};//parse using only newline and double quote
    char *tok;

    char *tempTitleId = malloc(10);
    char *tempType = malloc(10);
    char *tempTitle = malloc(25);
    char *tempYear = malloc(5);
    char *tempRuntime = malloc(4);
    char *tempGenres = malloc(5);
    int count = 0;
    int IDNumber = 0;

    printf("The data for your movie is:\n");
    while(fgets(line, 300, fp) != 0) {
        tok = strtok(line, delim);      //Gets  TitleId token
        if (tok) tempTitleId = tok;
        tok = strtok(NULL, delim);      //Gets Type token
        if (tok) tempType = tok;
        tok = strtok(NULL, delim);      //Gets Title token
        if (tok) tempTitle = tok;
        tok = strtok(NULL, delim);      //Consume and ignore
        tok = strtok(NULL, delim);      //Consume and ignore
        tok = strtok(NULL, delim);      //Get Year token
        if (tok) tempYear = tok;
        tok = strtok(NULL, delim);      //Consume and ignore
        tok = strtok(NULL, delim);      //Get Runtime token
        if (tok) tempRuntime = tok;
        tok = strtok(NULL, delim);      //get GenresToken
        if (tok) tempGenres = tok;

        if (strcmp(tempType, "movie") == 0) {
            //Movie *movie = newMovie(tempTitleId, tempType, tempTitle, tempYear, tempRuntime, tempGenres);
            articleChecker(tempTitle);
            tempTitle = strlower(tempTitle);
            IDNumber = getIDNumber(tempTitleId);
            if (count == 0){
                root = insert(root, tempTitle, IDNumber);
                count++;
            }
            else{
                insert(root, tempTitle, IDNumber);
            }
            //Movie *movie = newMovie(tempTitleId, tempType, tempTitle, tempYear, tempRuntime, tempGenres);
            //printMovieSingleLine(movie);
            //free(movie);
        }
    }
    //printf("The inorder traversal is: \n");
    //printInorder(root);

//    Node* searchTerm = searchTree(root, "garraf  barcelona");
//    if (searchTerm == NULL){
//        printf("The specified title was not found\n");
//    }
//    else{
//        printf("%s\t\t\t%d\n", searchTerm->key, searchTerm->id);
//    }

    char *todaysDate = getDate();
    printf("%s\n", todaysDate);

    fclose(fp);
    return 0;
}