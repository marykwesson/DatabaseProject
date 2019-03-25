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
bool searchMovie();
bool addMovie();
bool deleteMovie();
bool updateMovie();

int main(void){
    printf("Loading lookup file...\n");
    //clock_t bt,st;
    //bt = clock();
    Node *searchTree = fileReader("data.tsv");
    //Node *searchTree = fileReader("movie_records");
    //bt = clock() - bt;
    //st = clock();

    //char *searchTerm = cleanString("The Avengers");

    //Node* resultTree = searchResults(searchTree, searchTerm, NULL);
    //printInorder(resultTree);

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
            updateCase(searchTree);
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
        printf("%s.log was created", userName);
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
                bool searchTest = searchMovie(lookupTable);
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

bool searchMovie(Node *lookupTable){
    char movieTitle[100];
    printf("Enter a movie\n");
    scanf(" %s", movieTitle);
    while ((getchar()) != '\n');
    char *searchTerm = cleanString(movieTitle);
    Node* resultTree = searchResults(lookupTable, searchTerm, NULL);
    if (resultTree == NULL){
        printf("This movie does not exist in the lookup table");
        return false;
    }
    else{
        Movie *searchResults[10];
        int index = 0;
        for (int i = 0; i < 10; i++){
            searchResults[i] = newBlankMovie();
        }
        int temp = putInArray(resultTree, searchResults, index);
        for (int j = 0; j < 10; j++){
            printf("%d. %s (%s)\n", searchResults[j]->titleId, searchResults[j]->primaryTitle, searchResults[j]->year);
        }
        //display 15 possible movie titles
        //ask the user to pick one
        //return that movie
        return true;
    }
}