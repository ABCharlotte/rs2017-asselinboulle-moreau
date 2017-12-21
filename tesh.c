#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#include "red.h"
#include "cd.h"
#include "prompt.h"
#include "ench.h"

//fonction replacée par strtok
//cf brouillon si tu veux voir ;p


int main() {
				//TEST printf("pour arrêter le tesh il faut faire CRTL^C\n");
				if(isatty(0)){
					prompt(); //printf("PATH > ");
				}

//ligne = buffer stockage de l'entrée, mots : ligne découpée
				char *ligne;
				//ligne de commande fait moins de 100 caractères
				ligne = malloc(sizeof(char) * 100);
				char  **mots;
				// les mots : on considère qu'il y en a max 10
				mots = malloc(sizeof(char*) * 10);
				int cas_gal = 0;

// boucle infinie pour être toujours en attente
				while(1){
		//lire la ligne
							cas_gal=0;

							fgets(ligne, 100 , stdin);
							//TEST printf("j'ai pris note, je vais executer %s \n", ligne); //%s",buff);
							if(ligne==NULL || ligne[0]=='\0'){
								return 0;
							}
		// découpage en mots
							char * mot_temp;
							int i=0; // nb de mots
							mot_temp = strtok(ligne, " \n");//decoupeMots(ligne);
							//TEST printf("%s\n", mot_temp);
							while (mot_temp!=NULL && mot_temp!='\0' && strlen(mot_temp)>0 && i<10 ){ // && strlen(mot_temp)!=0 ){
										/*if (!strcmp(mot_temp,"\n")){
											//TEST printf("fin mots\n");
											i=9;
										}

										if (!strcmp(mot_temp," ")){
											//TEST printf("le mot est vide\n");
										} else {*/
											mots[i]=malloc(sizeof(char)*(1+strlen(mot_temp)));
											mots[i]=mot_temp;
											//TEST printf("%s\n", mot_temp);
											//TEST printf("le mot %d est %s\n",i,mots[i]);
											i++;
											mot_temp = strtok(NULL," \n");
											cas_gal = 1;
										//}
							}


		//cas particuliers
		//cd
							if (strcmp(mots[0],"cd")==0){
								//TEST printf("il s'agit d'un cd\n");
								Cd(mots);
								wait(NULL);
								cas_gal=0;
								/*if(isatty(0)){
									prompt(); //printf("PATH > ");
								}*/
							}

		//redirection & enchainement;
							char ** cmd1;
							cmd1 = malloc(sizeof(char*) * 10 );
							for (int j=0; j<i;j++){
										if ((strcmp(mots[j],"|")==0 || strcmp(mots[j],">")==0 || strcmp(mots[j],">>")==0 || strcmp(mots[j],"<")==0 ) ){
												//TEST	printf("il s'agit d'une redirection\n");
												cas_gal=0;
												char ** cmd2;
												cmd2 = malloc(sizeof(char*) * (i-j));
												for(int k=j+1;k<i;k++){
														cmd2[k-j-1]=malloc(sizeof(char)*(1+strlen(mots[k])));
														cmd2[k-j-1]=mots[k];
														//TEST	printf("cmd2[%d] : %s\n",k-j-1, cmd2[k-j-1] );
												}
												Red(mots[j], cmd1, cmd2);
												wait(NULL);
												//TEST printf("DONE\n");
												free (cmd2);
												/*if(isatty(0)){
													prompt(); //printf("PATH > ");
												}*/
												break;
										}else if ((strcmp(mots[j],";")==0 || strcmp(mots[j],"||")==0 || strcmp(mots[j],"&&")==0 ) ){
												//TEST printf("il s'agit d'un enchainement \n");
												cas_gal=0;
												char ** cmd2;
												cmd2 = malloc(sizeof(char*) * (i-j));
												for(int k=j+1;k<i;k++){
														cmd2[k-j-1]=malloc(sizeof(char)*(1+strlen(mots[k])));
														cmd2[k-j-1]=mots[k];
														//TEST printf("cmd2[%d] : %s\n",k-j-1, cmd2[k-j-1] );
												}
												ench(mots[j], cmd1, cmd2);
												wait(NULL);
												//TEST printf("DONE\n");
												free (cmd2);/*
												if(isatty(0)){
													prompt(); //printf("PATH > ");
												}*/
												break;
										} else {
												cmd1[j]=malloc(sizeof(char)*(1+strlen(mots[j])));
												cmd1[j] = mots[j];
												//TEST	printf("cmd1 : %s\n", cmd1[j] );
										}
							}
							free (cmd1);
							int end=1;
							//TEST printf("end\n");


		//cas général
							if (cas_gal && end){
									end=0;
									cas_gal=0;
									//TEST	printf("begin\n");
									if (!fork()){ //c'est le fils qui exécute la commande
											//TEST	printf("je suis au point d'exécution, je vais exécuter %s\n", mots[0] );
											execvp(mots[0],mots);
											exit(1); //on ne revient pas d'un exec
									}
									wait(NULL);
									//printf("here\n");
									/*if(isatty(0)){
										prompt(); //printf("PATH > ");
									}*/
							}
//remise à zeros
							for(int s=i-1;s>=0;s--){
								if(*(mots+s)!=NULL){
									//TEST printf("libération de %d\n",s );
									*(mots+s)=NULL;
								}
							}

							if(isatty(0) && ligne[0]!='\0'){
								prompt(); //printf("PATH > ");
							}
							ligne=NULL;
							free(ligne);
							free(mots);
							//TEST printf("Free\n");
							ligne = malloc(sizeof(char) * 100);
							mots = malloc(sizeof(char*) * 10);
							//prompt();


		//gestion du CRTL^C
						//if SIGINT free tout

				}
//FIN
				free(ligne);
				free(mots);
			  return 0;
}
