CC=gcc
CFLAGS=-Wall

#cible: dependance
#	commandes

tesh : tesh.o cd.o red.o prompt.o
	gcc -std=c99 -o tesh tesh.o red.o cd.o prompt.o

cd.o : cd.c
	gcc -std=c99 -o cd.o -c cd.c

red.o : red.c
	gcc -std=c99 -o red.o -c red.c

prompt.o : prompt.c
	gcc -std=c99 -o prompt.o -c prompt.c

tesh.o : tesh.c red.h cd.h prompt.h
	gcc -std=c99 -o tesh.o -c tesh.c

clean :
	@rm -rf *.o
	@rm -f tesh
#hello: hello.o main.o
#	gcc -o hello hello.o main.o

#hello.o: hello.c
#	gcc -o hello.o -c hello.c -W -Wall -ansi -pedantic

#main.o: main.c hello.h
#	gcc -o main.o -c main.c -W -Wall -ansi -pedantic
