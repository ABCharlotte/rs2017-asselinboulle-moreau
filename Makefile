CC=gcc
CFLAGS=-Wall

#cible: dependance
#	commandes

tesh : tesh.o cd.o red.o
	gcc -o tesh tesh.o red.o cd.o

cd.o : cd.c
	gcc -o cd.o -c cd.c

red.o : red.c
		gcc -o red.o -c red.c

tesh.o : tesh.c red.h cd.h
	gcc -o tesh.o -c tesh.c

clean :
	@rm -rf *.o
	@rm -f tesh
#hello: hello.o main.o
#	gcc -o hello hello.o main.o

#hello.o: hello.c
#	gcc -o hello.o -c hello.c -W -Wall -ansi -pedantic

#main.o: main.c hello.h
#	gcc -o main.o -c main.c -W -Wall -ansi -pedantic
