#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//char *commande[1000];
//char *doss;
//int errno;

int fd[2];
pipe(fd);

void Red(char *type, char **cmd1, char**cmd2) {
	//TEST printf("suis dans la boucle de redirection \n" );
	//TEST printf("je vais faire %s %s %s \n", cmd1[0], type, cmd2[0] );
	//if(commande[1]=='>'){
	if(!strcmp(type,">")){
//pipe pour rediriger sortie vers fichier
	}
	else if(!strcmp(type,">>")){
//pipe pour rediriger sortie vers fin de fichier
	}
	else if(!strcmp(type,"<")){
//pipe pour éxécuter cmd1 avec fichier comme entrée
		if (!fork()){
			int fd=open(cmd2[0]);
			dup2(fd,0);
			//TEST			printf("je vais lire %s et l'écrire sur %s\n", cmd2[0],cmd1[0] );
			close(fd);
			execvp(cmd1[0],cmd1);
			exit(1);
		}
		wait(NULL);
		//TEST		printf("j'ai fais\n" );
	} // TODO A revoir 
	else if(!strcmp(type,"|")){
		printf("je vais faire le pipe \n");
		if (fork()==0){
			//fils exécute cm1
			dup2(1,fd[1]);
			close(fd[1]);
			close(fd[0]);
			printf("exec cmd1\n");
			execvp(cmd1[0], cmd1);
			exit(1);
		}
		//père execute cm2 avec le retour de cm1
		wait(NULL);
		dup2(fd[0],0);
		close(fd[1]);
		close(fd[0]);
		printf("exec cmd2\n");
		execvp(cmd2[0], cmd2);
		exit(1);
	}
	//TEST 		printf("fin de la redirection\n" );
}
/* code valentin :

elseif(commande[1]=='|'){

	if (fork()==0){
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execvp(cmd1[0], cmd1);
		exit(1);
	}
	if (fork()==0){
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execvp(cmd2[0], cmd2);
		exit(1);
	}
	wait(NULL);
	wait(NULL);
*/
