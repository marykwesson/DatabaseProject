//
// Created by bamam on 3/13/2019.
//

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
//#include "movie.h"
//#include "avl.h"
#include <stdbool.h>
#include "datasetReader.h"
#include "userLogs.h"

#define MAX_FILE_NAME 100

void createCase();
void readCase();
void deleteCase();
void updateCase();
Movie *searchMovie();
bool addMovie();
bool deleteMovie();
bool updateMovie();

int main(void){
    printf("Loading lookup file...\n");
    //clock_t bt,st;
    //bt = clock();
    Node *lookupTree = fileReader("data.tsv");
    //Node *searchTree = fileReader("movie_records");
    //bt = clock() - bt;
    //st = clock();
    //printInorder(lookupTree);
    //char line[256];   //1
    //char *line = (char*)malloc(256);
    /*char* movieTitle;  //2
    printf("Enter a movie\n");//3
    //gets(movieTitle);
    //fgets(movieTitle, 20, stdin);
    fgets(line, sizeof(line), stdin);//4
    char *tok = strtok(line, "\n"); //5     //Gets  TitleId token
    if (tok) movieTitle = tok;//6
    //char *movieTitle2;
    //movieTitle2 = movieTitle;
    printf("The movie title is %s", movieTitle);//7
    //free(movieTitle);
    //char* newMovieTitle = &movieTitle[0];
    //scanf("%[^\n]%*c", movieTitle);
    //scanf(" %s", movieTitle);
    //cleanInput(fgets(movieTitle, sizeof(movieTitle), stdin));
    //while ((getchar()) != '\n');
    //char *searchTerm = malloc(strlen(movieTitle + 1));
    char *searchTerm = cleanString(movieTitle);//8

    //free(movieTitle);
    //printf("You entered: %s", searchTerm);
    //char *searchTerm = cleanString("Big apple");
    //char* searchTerm2 = searchTerm;
    Node* resultTree = NULL;//9
    //resultTree = searchResults(lookupTree, searchTerm, resultTree);
    //printf("You entered: %s", cleanString(movieTitle));
    resultTree = searchResults(lookupTree, searchTerm , resultTree);
    //printf("Temp is: %d", temp);
    if(resultTree == NULL){//10
        printf("No match was found\n");//11
    }//12
    else {//13
        printInorder(resultTree);//14
    }*/
    //st = clock() - st;

    //double build_time = ((double)bt)/CLOCKS_PER_SEC; // in seconds
    //double search_time = ((double)st)/CLOCKS_PER_SEC; // in seconds

    //printf("Loaded %d movies\n", getLeafCount(searchTree));
    printf("Lookup file was successfully loaded.\n\n");
    //printf("Loaded %d movies\n", getCount(searchTree));
    //printf("took %f seconds to build tree \n", build_time);
    //printf("took %f seconds to search tree \n", search_time);

    //createUserLog("MaryK");
    //readUserLog("MaryK");

    char userActivity;
    bool validUserActivity = false;
    do{
        printf("Enter C to create a new user file, R to display a user file, "
               "U to update a user file, and D to delete a user file, and E to exit\n");
        scanf(" %c", &userActivity);
        while ((getchar()) != '\n');
        if (userActivity == 'C' || userActivity == 'c'){
            printf("The user chose create\n");
            //bool complete = createCase();
            createCase();
            /*if (complete == true){
                //validUserActivity = true;
            }
            else {
                printf("Redirecting to Start Menu\n");
            }*/
        }
        else if (userActivity == 'R' || userActivity == 'r'){
            printf("The user chose read\n");
            //bool complete = readCase();
            readCase();
            /*if (complete == true){
                //validUserActivity = true;
            }
            else {
                printf("Redirecting to Start Menu\n");
            }*/
        }
        else if (userActivity == 'U' || userActivity == 'u'){
            printf("The user chose update\n");
            //bool complete = updateCase();
            updateCase(lookupTree);
            /*if (complete == true){
                //validUserActivity = true;
            }
            else {
                printf("Redirecting to Start Menu\n");
            }*/
        }
        else if (userActivity == 'D' || userActivity == 'd'){
            printf("The user chose delete\n");
            //bool complete = deleteCase();
            deleteCase();
            /*if (complete == true){
                validUserActivity = true;
            }
            else {
                printf("Redirecting to Start Menu\n");
            }*/
        }
        else if (userActivity == 'E' || userActivity == 'e'){
            validUserActivity = false;
            return 0;
        }
        else{
            printf("The value you entered was invalid. Please try again.\n");
        }
    }while (!validUserActivity);


    return 0;
}

void createCase(){
    char userName[15];
    printf("Enter the users name (There is a 15 character limit)\n");
    scanf(" %15s", userName);
    while ((getchar()) != '\n');
    if (exists(userName) != 0) {
        printf("This username already exists\n");
        //return false;
    } else {
        createUserLog(userName);
        printf("%s.log was created\n", userName);
        //return true;
    }
}

void readCase(){
    char userName[15];
    printf("Enter the users name (There is a 15 character limit)\n");
    scanf(" %15s", userName);
    while ((getchar()) != '\n');
    if (exists(userName) == 1) {
        readUserLog(userName);
        //return true;
    } else {
        printf("This username doesn't exists.\n");
        //return false;
    }
}

void updateCase(Node *lookupTable){
    char userChoice;
    bool finished = false;
    char userName[15];
    printf("Enter the users name (There is a 15 character limit)\n");
    scanf(" %15s", userName);
    while ((getchar()) != '\n');
    if (exists(userName) == 1) {

        do{
            printf("Enter A to add movie, D to delete movie, U to update movie, or E to exit to start menu\n");
            scanf(" %c", &userChoice);
            while ((getchar()) != '\n');
            if (userChoice == 'A' || userChoice == 'a'){
                printf("The User chose add\n");
                Movie* searchTest = searchMovie(lookupTable);
                if (searchTest->primaryTitle != NULL){
                    printf("You selected\n%s (%s)\n", searchTest->primaryTitle, searchTest->year);
                    printLine(searchTest);
                    writeUserLog(searchTest, userName);
                }
                else{
                    finished = true;
                }
            }
            else if (userChoice == 'D' || userChoice == 'd'){
                printf("The User chose delete");
                //delete movie function
            }
            else if (userChoice == 'U' || userChoice == 'u'){
                printf("The User chose update");
                //update movie function
            }
            else if (userChoice == 'E' || userChoice == 'e'){
                finished = true;
            }
            else{
                printf("Invalid Input");
            }
        }while (!finished);

        //return true;
    } else {
        printf("This username doesn't exists.\n");
        //return false;
    }
}

void deleteCase(){
    char userName[15];
    printf("Enter the users name (There is a 15 character limit)\n");
    scanf(" %15s", userName);
    while ((getchar()) != '\n');
    if (exists(userName) == 1) {
        deleteUserLog(userName);
        //return true;
    } else {
        printf("This username doesn't exists.\n");
        //return false;
    }
}

Movie *searchMovie(Node *lookupTable) {
    char line[256];
    char *movieTitle;
    char movieNumber;
    bool valid = false;
    printf("Enter a movie\n");
    fgets(line, sizeof(line), stdin);
    char *tok = strtok(line, "\n");      //Gets  TitleId token
    if (tok) movieTitle = tok;
    char *searchTerm = cleanString(movieTitle);
    printf("You are searching for: %s\n", searchTerm);
    Node *resultTree = NULL;
    resultTree = searchResults(lookupTable, searchTerm, resultTree);
    //resultTree = searchResults(lookupTree, searchTerm , resultTree);
    //printInorder(resultTree);
    //free(resultTree);
    if (resultTree == NULL) {
        printf("This movie does not exist in the lookup table");
        return NULL;
    } else {
        Movie *resultsArray[10];
        int index = 0;
        for (int i = 0; i < 10; i++) {
            resultsArray[i] = newBlankMovie();
        }

        int temp = 0;

        temp = putInArray(resultTree, resultsArray, index);
        //temp = putInArray(resultTree, searchResults, index);
        free(resultTree);
        //printf("Temp is: %d\n", temp);
        //printf("index is: %d\n", index);

        if (temp == 0) {
            printf("Error");
        }
        for (int j = 0; j < 10; j++) {
            if (resultsArray[j]->primaryTitle != NULL){
                printf("%d. %s (%s)\n", resultsArray[j]->titleId, resultsArray[j]->primaryTitle, resultsArray[j]->year);
            }
        }
        do {
            printf("Select an index using the numbers above or enter E to return to the start menu\n");
            scanf(" %c", &movieNumber);
            if (movieNumber == 'E' || movieNumber == 'e') {
                valid = true;
                return newBlankMovie();
            } else if (movieNumber >= '0' && movieNumber <= '9') {
                valid = true;
                int index = movieNumber - '0';
                return resultsArray[index];
            } else {
                printf("Invalid Input.");
            }
        } while (!valid);
    }
    return NULL;
}
