#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


//char *commande[1000];
//char *doss;
//int errno;

void Red(char *type, char **cmd1, char**cmd2) {

		int fd_in;
		int fd_out;
		int fd[2];
		pipe(fd);
		//TEST printf("suis dans la boucle de redirection \n" );
		//TEST printf("je vais faire %s %s %s \n", cmd1[0], type, cmd2[0] );

		if(type[0]=='>') { // On a affaire a une redirection sortante
			if(type[1] != '\0' &&  type[1] == '>') { // on a affaire a une redirection sortant qui ajoute a la fin
				fd_out = open(cmd2[0], O_WRONLY|O_CREAT|O_APPEND,0644); // Append pour ajouter
			} else { //redirection sortant pas qui ajoute
				fd_out = open(cmd2[0], O_WRONLY|O_CREAT|O_TRUNC,0644);
			}


			if(!fork()){
				dup2(fd_out,1);
				close(fd_out);

				execvp(cmd1[0], cmd1);
				exit(1);
			}
			wait(NULL);


		/*if(!strcmp(type,">")){ //TODO à refaire (on doit écrire la sortie sur le fichier et pas faire ce que je fais x'))
							//rediriger sortie vers fichier
							if (!fork()){
									fd[0]=open(cmd2[0]);
									dup2(fd[0],0);
									//TEST
										//printf("je vais lire %s et l'écrire sur %s\n", cmd1[0],cmd2[0] );
										//en vrè printf("je redirige la sortie de cmd1 vers le fichier cmd2")
									close(fd[0]);
									execvp(cmd1[0],cmd1);
									exit(1);
							}
							wait(NULL);*/
		} else if(!strcmp(type,"<")){
						//pipe pour exécuter cmd1 avec fichier cmd2 comme entrée
						fd_in=open(cmd2[0], O_RDONLY);

						if (!fork()){
							dup2(fd_in,0);
							//TESTprintf("je vais lire %s et l'écrire sur %s\n", cmd2[0],cmd1[0] );
							close(fd_in);
							if (!strcmp(cmd1[0],"cat")){
								execlp(cmd1[0],cmd1[0],NULL);
							}
							execvp(cmd1[0],cmd1);
							exit(1);
						}
						wait(NULL);
						//TEST printf("j'ai fais\n" );

		}else if(!strcmp(type,"|")){ // TODO A revoir
						//printf("je vais faire le pipe \n");

						if (fork()==0){
							//fils exécute cm1
							close(fd[0]);
							dup2(fd[1],1);
							//close(fd[1]);
							//printf("exec cmd1\n");
							execvp(cmd1[0], cmd1);
							exit(1);
						}
						//wait(NULL);
						//printf("DONE1\n");
						//else {
							//wait(NULL);
							if (fork()==0){
								//wait(NULL);
								close(fd[1]);
								dup2(fd[0],0);
								//close(fd[0]);
								//printf("exec cmd2\n");
								execvp(cmd2[0], cmd2);
								exit(1);
							//}else{
								//wait(NULL);
						//wait(NULL);
						//printf("DONE2\n");
							}
					//}
					close(fd[0]);
					close(fd[1]);

					wait(NULL);
					//printf("DONE2\n");
		}

		//TEST 		printf("fin de la redirection\n" );
}
