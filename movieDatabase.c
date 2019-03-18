//
// Created by bamam on 3/13/2019.
//

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
//#include "movie.h"
//#include "avl.h"
#include "datasetReader.h"
#include "userLogs.h"

#define MAX_FILE_NAME 100

int main(void){
    clock_t bt,st;
    bt = clock();
    Node *searchTree = fileReader("data.tsv");
    //Node *searchTree = fileReader("movie_records");
    bt = clock() - bt;
    st = clock();

    char *searchTerm = cleanString("Invaders from Planet Zero");

    Node* resultTree = searchResults(searchTree, searchTerm, NULL);
    printInorder(resultTree);

    st = clock() - st;

    double build_time = ((double)bt)/CLOCKS_PER_SEC; // in seconds
    double search_time = ((double)st)/CLOCKS_PER_SEC; // in seconds

    printf("Loaded %d movies\n", getLeafCount(searchTree));
    printf("Loaded %d movies\n", getCount(searchTree));
    printf("took %f seconds to build tree \n", build_time);
    printf("took %f seconds to search tree \n", search_time);

    //createUserLog("MaryK");
    readUserLog("MaryK");

    return 0;
}