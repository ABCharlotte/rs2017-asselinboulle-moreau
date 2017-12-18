#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

//char *commande[1000];
//char *doss;
//int errno;

void Red(char *type, char **cmd1, char**cmd2) {
		int fd[2];
		pipe(fd);
		//TEST printf("suis dans la boucle de redirection \n" );
		//TEST printf("je vais faire %s %s %s \n", cmd1[0], type, cmd2[0] );
		if(!strcmp(type,">")){ //TODO à refaire (on doit écrire la sortie sur le fichier et pas faire ce que je fais x'))
							//rediriger sortie vers fichier
							if (!fork()){
									fd[0]=open(cmd1[0]);
									dup2(fd[0],0);
									//TEST
										printf("je vais lire %s et l'écrire sur %s\n", cmd1[0],cmd2[0] );
									close(fd[0]);
									execvp(cmd2[0],cmd2);
									exit(1);
							}
							wait(NULL);

		}else if(!strcmp(type,">>")){
						//pipe pour rediriger sortie vers fin de fichier

		}else if(!strcmp(type,"<")){
						//pipe pour éxécuter cmd1 avec fichier comme entrée
						if (!fork()){
							fd[0]=open(*cmd2);
							dup2(fd[0],0);
							//TESTprintf("je vais lire %s et l'écrire sur %s\n", cmd2[0],cmd1[0] );
							close(fd[0]);
							execlp(cmd1[0],cmd1[0],NULL);
							exit(1);
						}
						wait(NULL);
						//TEST printf("j'ai fais\n" );

		}else if(!strcmp(type,"|")){ // TODO A revoir
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
