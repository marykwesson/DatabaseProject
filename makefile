OBJS = movieDatabase.o movie.o avl.o datasetReader.o userLogs.o -o movieDatabase
LOPTS = -Wall -Wextra -std=c11 -g 
OOPTS = $(LOPTS) -c

all : movieDatabase

movieDatabase : movieDatabase.o movie.o avl.o datasetReader.o userLogs.o
	gcc $(LOPTS) $(OBJS)
	
movieDatabase.o : movieDatabase.c datasetReader.h userLogs.h
	gcc $(OOPTS) movieDatabase.c
	
movie.o : movie.c movie.h
	gcc $(OOPTS) movie.c

avl.o : avl.c avl.h movie.h
	gcc $(OOPTS) avl.c
	
datasetReader.o : datasetReader.c datasetReader.h avl.h
	gcc $(OOPTS) datasetReader.c

userLogs.o : userLogs.c userLogs.h
	gcc $(OOPTS) userLogs.c

clean :
	rm -f movieDatabase.o movie.o avl.o datasetReader.o userLogs.o movieDatabase
