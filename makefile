

CC=gcc
CFLAGS= -c -Wall

all:mi run

mi:Minor.o
	$(CC) Minor.o -o mi

Minor.o:Minor.c
	$(CC) $(CFLAGS) Minor.c
run:mi 
	./mi
	
clean :
	rm -rf *o mi 




