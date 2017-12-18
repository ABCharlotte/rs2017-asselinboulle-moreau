#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


char *commande[1000];
char *doss;
int errno;
int status;

void ench(char *type, char **cmd1, char**cmd2){
	if(fork()==0){
		execvp(cmd1[0], cmd1); //execution commande 1
	}
	wait(&status);
	if(!strcmp(type,";")){ //je pense pas que l'on peut comparer comme ça
		if(fork()==0){
			execvp(cmd2[0], cmd2); //execution commande 2
		}
		wait(NULL);
	}else if(!strcmp(type,"&&") && (WEXITSTATUS(status)==0)){ //idem + test retour =0
		if(fork()==0){
			execvp(cmd2[0], cmd2); //execution commande 2
		}
		wait(NULL);
	}else if(!strcmp(type,"||") && (WEXITSTATUS(status)!=0)){ //idem + test retour !=0
		if(fork()==0){
			execvp(cmd2[0], cmd2); //execution commande 2
		}
		wait(NULL);
	}
}