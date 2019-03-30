OBJS = movieDatabase.o avl.o datasetReader.o userLogs.o -o movieDatabase
LOPTS = -Wall -Wextra -std=c11 -g 
OOPTS = $(LOPTS) -c

all : movieDatabase

movieDatabase : movieDatabase.o avl.o datasetReader.o userLogs.o
	gcc $(LOPTS) $(OBJS)
	
movieDatabase.o : movieDatabase.c datasetReader.h userLogs.h
	gcc $(OOPTS) movieDatabase.c

avl.o : avl.c avl.h
	gcc $(OOPTS) avl.c
	
datasetReader.o : datasetReader.c datasetReader.h avl.h
	gcc $(OOPTS) datasetReader.c

userLogs.o : userLogs.c userLogs.h
	gcc $(OOPTS) userLogs.c

clean :
	rm -f movieDatabase.o avl.o datasetReader.o userLogs.o movieDatabase
