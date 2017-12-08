#include <stdio.h>
#include <unistd.h>
#include <string.h>

char *commande[1000];
char *doss;
int errno;
int status;

int ench(){
	if(fork()==0){
		exec1p("cmd1", "cmd1", NULL); //execution commande 1
	}
	wait(&status);
	if(commande[1]==';'){ //je pense pas que l'on peut comparer comme ça
		if(fork()==0){
			exec1p("cmd2", "cmd2", NULL); //execution commande 2
		}
		wait(NULL);
	}elseif(commande[1]=='&&' && WEXITED(status) && (WEXITSTATUS(status)==0)){ //idem + test retour =0
		if(fork()==0){
			exec1p("cmd2", "cmd2", NULL); //execution commande 2
		}
		wait(NULL);
	}elseif(commande[1]=='||' && WEXITED(status) && (WEXITSTATUS(status)!=0)){ //idem + test retour !=0
		if(fork()==0){
			exec1p("cmd2", "cmd2", NULL); //execution commande 2
		}
		wait(NULL);
	}
	return 0;
}