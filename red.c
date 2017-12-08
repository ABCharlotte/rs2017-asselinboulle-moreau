#include <stdio.h>
#include <unistd.h>
#include <string.h>

char *commande[1000];
char *doss;
int errno;
int fd[2];
pipe(fd);

int red() {
	if(commande[1]=='>'){
//pipe pour rediriger sortie vers fichier
	}
	elseif(commande[1]=='>>'){
//pipe pour rediriger sortie vers fin de fichier
	}
	elseif(commande[1]=='<'){
//pipe pour éxécuter cmd1 avec fichier comme entrée
	}
	elseif(commande[1]=='|'){
		if (fork()==0){
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			exec1p("cmd1", "cmd1", NULL);
		}
		if (fork()==0){
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			exe1p("prog2", "prog2", NULL);
		}
		wait(NULL);
		wait(NULL);
	}
}