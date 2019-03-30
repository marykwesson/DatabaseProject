//
// Created by bamam on 3/13/2019.
//
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLDBLACK "\033[1m\033[30m"

#define BACKRED "\033[41m"
#define BACKGREEN "\033[42m"
#define BACKYELLOW "\033[43m"
#define BACKBLUE "\033[44m"
#define BACKMAGENTA "\033[45m"
#define BACKCYAN "\033[46m"
#define BACKWHITE "\033[47m"

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
Node *searchMovie(Node* root);
//bool addMovie();
Node* deleteMovie(Node* root);
Node* updateMovie(Node* root);

int main(void){
    printf(BOLDBLACK "Loading lookup file...\n" RESET);

    Node *lookupTree = fileReader("movie_records");

    printf("%d movies were loaded\n", getCount(lookupTree));

    char userActivity;
    bool validUserActivity = false;
    do{
        printf(BACKWHITE BLACK "MAIN MENU" RESET);
        printf("\n");
        printf("Enter C to create a new user file, R to display a user file, "
               "U to update a user file, and D to delete a user file, and E to exit\n");
        scanf(" %c", &userActivity);
        while ((getchar()) != '\n');
        if (userActivity == 'C' || userActivity == 'c'){
            printf(BACKGREEN "Create a New User Log" RESET);
            printf("\n");
            createCase();
        }
        else if (userActivity == 'R' || userActivity == 'r'){
            printf(BACKMAGENTA "Read/Print a User Log" RESET);
            printf("\n");
            readCase();
        }
        else if (userActivity == 'U' || userActivity == 'u'){
            printf(BACKBLUE "Update a User Log" RESET);
            printf("\n");
            updateCase(lookupTree);
        }
        else if (userActivity == 'D' || userActivity == 'd'){
            printf(BACKRED "Delete a User Log" RESET);
            printf("\n");
            deleteCase();
        }
        else if (userActivity == 'E' || userActivity == 'e'){
            validUserActivity = false;
            return 0;
        }
        else{
            printf(RED "The value you entered was invalid. Please try again.\n" RESET);
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
        printf(RED "This username already exists\n" RESET);
        //return false;
    } else {
        createUserLog(userName);
        printf(GREEN "%s.log was created\n" RESET, userName);
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
        Node * userLogTree = NULL;
        userLogTree = readLogIntoTree(userLogTree, userName);
        do{
            printf("Enter A to add movie, D to delete movie, U to update movie, or E to exit to start menu\n");
            scanf(" %c", &userChoice);
            while ((getchar()) != '\n');
            if (userChoice == 'A' || userChoice == 'a'){
                char typechoice;
                printf("The User chose add\n");
                Node* searchTest = searchMovie(lookupTable);
                if (searchTest != NULL && searchTest->id != 99){
                    printf("You selected\n%s (%s)\n", searchTest->title, searchTest->year);
                    changeDate(searchTest, getDate());
                    printf("Enter B for blu-ray, D for DVD and G for digital.\n");
                    scanf(" %c", &typechoice);
                    while ((getchar()) != '\n');
                    if (typechoice == 'B' || typechoice == 'b' || typechoice == 'D' || typechoice == 'd' || typechoice == 'G' || typechoice == 'g'){
                        changeType(searchTest, typechoice);
                    }
                    else{
                        printf("You entered an invalid value. The default type of DVD will be used. It can be changed by updateing the movie\n");
                        changeType(searchTest, 'D');
                    }
                    if (userLogTree == NULL){
                        userLogTree = insert(userLogTree, searchTest->key, searchTest->id, 
                            searchTest->title, searchTest->genres, searchTest->runningTime, searchTest->year, searchTest->date, searchTest->type);
                    }
                    else{
                        insert(userLogTree, searchTest->key, searchTest->id, 
                            searchTest->title, searchTest->genres, searchTest->runningTime, searchTest->year, searchTest->date, searchTest->type);
                    }
                }
                else{
                    finished = true;
                }
            }
            else if (userChoice == 'D' || userChoice == 'd'){
                printf("The User chose delete\n");
                if(userLogTree != NULL){
                    userLogTree = deleteMovie(userLogTree);
                }
                else{
                    printf("The user log is empty.\n");
                }
            }
            else if (userChoice == 'U' || userChoice == 'u'){
                printf("The User chose update\n");
                userLogTree = updateMovie(userLogTree);
            }
            else if (userChoice == 'R' || userChoice == 'r'){
                printf("The User chose retreive\n");
                //userLogTree = retreiveMovie(userLogTree);
            }
            else if (userChoice == 'E' || userChoice == 'e'){
                finished = true;
            }
            else{
                printf("Invalid Input");
            }
        }while (!finished);
        printf("Writing to the user file\n");
        writeUserLog(userLogTree, userName);
        free(userLogTree);
    } else {
        printf("This username doesn't exists.\n");
    }
}

void deleteCase(){
    char userName[15];
    printf(RESET "Enter the users name (There is a 15 character limit)\n" RESET);
    scanf(" %15s", userName);
    while ((getchar()) != '\n');
    if (exists(userName) == 1) {
        deleteUserLog(userName);
    } else {
        printf("This username doesn't exists.\n");
    }
}

Node *searchMovie(Node *lookupTable) {
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
    if (resultTree == NULL) {
        printf("This movie does not exist in the lookup table\n");
        return NULL;
    } else {
        Node *resultsArray[10];
        int index = 0;
        for (int i = 0; i < 10; i++) {
            resultsArray[i] = newNode("/0", 99, "/0", "/0", "/0", "/0", "/0", "/0");
        }

        int temp = 0;

        temp = putInArray(resultTree, resultsArray, index);
        free(resultTree);

        if (temp == 0) {
            printf("Error");
        }
        for (int j = 0; j < 10; j++) {
            if (resultsArray[j]->id != 99){
                printf("%d. %s (%s)\n", resultsArray[j]->id, resultsArray[j]->title, resultsArray[j]->year);
            }
        }
        do {
            printf("Select an index using the numbers above or enter E to return to the start menu\n");
            scanf(" %c", &movieNumber);
            if (movieNumber == 'E' || movieNumber == 'e') {
                valid = true;
                return NULL;
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

Node *deleteMovie(Node *userLog){
    //printInorder(userLog);
    Node* searchTerm = searchMovie(userLog);
    if (searchTerm != NULL){
        userLog = deleteNode(userLog, searchTerm->key);
    }
    else{
        printf("That movie does not exist in the user log\n");
    }
    return userLog;
}

Node *updateMovie(Node *userLog){
    bool finished = false;
    char userChoice;
    char ynchoice;
    char typechoice;
    Node *searchTerm = searchMovie(userLog);
    printf("Enter D to update the date, T to update the type, or E to exit.\n");
    scanf(" %c", &userChoice);
    while ((getchar()) != '\n');
    do{
        //if the search term exists let the user update stuff
        if (searchTerm != NULL){
            //Update date
            if (userChoice == 'D' || userChoice == 'd'){
                int dd,mm,yy;
                //Start of date do-while loop
                do{
                    printf("Enter date (DD/MM/YYYY format): ");
                    scanf("%2d%*c%2d%*c%4d",&dd,&mm,&yy);
                    while ((getchar()) != '\n');
                    char* date = malloc(11);
                    sprintf(date, "%d/%d/%d", dd,mm,yy);
                    //verify that the date is accurate
                    changeDate(searchTerm, date);
                    printf("Is %s the correct date? y/n (Enter E to exit)\n", date);
                    scanf(" %c", &ynchoice);
                    while ((getchar()) != '\n');
                    if (ynchoice == 'Y' || ynchoice == 'y'){
                        changeDate(searchTerm, date);
                        userLog = deleteNode(userLog, searchTerm->key);
                        if (userLog == NULL){
                            userLog = insert(userLog, searchTerm->key, searchTerm->id, 
                                searchTerm->title, searchTerm->genres, searchTerm->runningTime, 
                                searchTerm->year, searchTerm->date, searchTerm->type);
                        }
                        else{
                            insert(userLog, searchTerm->key, searchTerm->id, 
                                searchTerm->title, searchTerm->genres, searchTerm->runningTime, 
                                searchTerm->year, searchTerm->date, searchTerm->type);
                        }
                        finished = true;
                    }
                    else if (ynchoice == 'N' || ynchoice == 'n'){
                        //do nothing but don't exit
                    }
                    else if (ynchoice == 'E' || ynchoice == 'e'){
                        finished = true;
                    }
                    else{
                        printf("Incorrect Input\n");
                        finished = false;
                    }
                //end of date do while loop
                }while(!finished);
            }//end of update date
            //update type
            else if (userChoice == 'T' || userChoice == 't'){
                //start of type do-while loop
                do{
                    printf("Enter B for blu-ray, D for DVD and G for digital (Enter E to exit).\n");
                    scanf(" %c", &typechoice);
                    while ((getchar()) != '\n');
                    //if it a correct choice update it
                    if (typechoice == 'B' || typechoice == 'b' || typechoice == 'D' || typechoice == 'd' || typechoice == 'G' || typechoice == 'g'){
                        changeType(searchTerm, typechoice);
                        if (userLog == NULL){
                            userLog = insert(userLog, searchTerm->key, searchTerm->id, 
                                searchTerm->title, searchTerm->genres, searchTerm->runningTime, 
                                searchTerm->year, searchTerm->date, searchTerm->type);
                        }
                        else{
                            insert(userLog, searchTerm->key, searchTerm->id, 
                                searchTerm->title, searchTerm->genres, searchTerm->runningTime, 
                                searchTerm->year, searchTerm->date, searchTerm->type);
                        }
                        finished = true;
                    }
                    //If the user wants to exit this loop allow exit
                    else if (typechoice == 'E' || typechoice == 'e'){
                        finished = true;
                    }
                    //if they insert a wrong answer send them back to the start
                    else{
                        finished = false;
                    }
                //end of type do-while loop
                }while(!finished);
            }//end of update type
            //If the user wants to exit update
            else if (userChoice == 'E' || userChoice == 'e'){
                finished = true;
            }
            //if they insert an invalid value send them back to start
            else{
                printf(RED "Invalid Input. Type will not be changed\n" RESET);
                finished = true;
            }
        }//end of if the search term exists       
        else{
            printf("That movie does not exist in the user log\n"); 
        }
    }while(!finished); 
    return userLog;
}