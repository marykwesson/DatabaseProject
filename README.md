# DatabaseProject
Movie Database based on IMDB Datasets. Written for CS 201 Spring 2019 by Mary Katherine Wesson

## About
### Getting Started
1. Download basic from https://datasets.imdbws.com/title.basics.tsv.gz
2. Unzip the file
3. using commandline run grep "movie" title.basic.tsv > movie_records
4. make sure movie_records is in the DatabaseProject directory
5. Compile the project using make
6. Follow the instructions on screen

### Purpose
The purpose of this database is to act as a personal media library. It allows user to track the movies they own and take advantage on the IMDB dataset to keep accurate information on each movie.

### Options

Main Options
1. Create user - allows user to create their own user catolog
2. Read user - allows user to print the contents of their user catolog
3. Update user - allows user to update the contents of their user catolog (see below)
4. Delete user - allows user to delete their user catolog

Update user Options
1. Add movie - allows user to add a movie to their catolog
2. Delete movie - allows user to delete a movie from their catolog
3. Update movie - allows user to change the date and/or type of a movie in their catolog
4. Retrieve movie - allows user to print a single movie from their catolog

### Design Choice Reasoning

**Data Structure**
- I chose to use an AVL tree because it can insert, search, and delete in O(lg n) time. This program is required to insert over 500,000 movies into a data structure, at the start of the program, making quick insertion a necessity. Additionally, each time a movie is added to the catolog the program must search for every instance starting with the search term inserted. This would be incredibly slow with any sory of sorting algorithm.
- I chose to use an AVL tree instead of a binary search tree because it would be more evenly distributed and therefore quicker.
- I chose to keep all of my movie data in my AVL node structure because it would allow me to only use one data structure in my program and make the program cleaner. By doing so I was also able to read user logs into trees instead of arrays and that allowed me to not limit the number of movies in the user log and sort it advantageously when being updates.
- There are many reasources for AVL trees out there since it is a well know data structure. I used geeks for geeks examples as a starting point and changed it to meet my needs. This required changing all of the compares and adding additional states. Some of the avl function are very similar. This is caused by there being one way to do them. For example, with exception of the printf() statement my printInorder() function is exactly the same as ones online because it is a well known recursive solution to recurse left, print, recurse right. Attempting to find another solution would be time consuming and most likely result in a less optimal solution.

**Movie Selection**
- I chose to only allow the user to chose from 10 movies when searching the dataset because any instance of an exact match will be returned first. Most series of movies have under 10 movies and this requires the user to be more specific if they want to search for a movie. In a second iteration of this program I plan on adding an option to narrow the search by year.

**Colors**
- I chose to color code the states of the program in an attempt to keep it clear what state you are in. Using an ASCII interface has a tendency to make it easy to get lost in a program with many states and using the colors allows the user to easily find what state they are in by looking just a few line up. All of the main states query the user for their username and all of the update user states query the user to enter a movie. If you are moving quickly it is easy to accidentally get your current state confused and insert an incorrect answer. While the program checks for an incorrect input at times it can send you back further than you might like.