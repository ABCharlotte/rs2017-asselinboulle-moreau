#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "red.h"
#include "cd.h"

//fonction replacée par strtok
//cf brouillon si tu veux voir ;p


int main() {
	printf("pour arrêter le tesh il faut faire CRTL^C\n");
	printf("PATH > ");//TODO %S €",$PATH);

//ligne = buffer stockage de l'entrée : on considère qu'une ligne de commande fait moins de 1000 caractères
	char *ligne;
	ligne = malloc(sizeof(char) * 100);
	char  **mots;
// les mots : on considère qu'il y en a max 10
	mots = malloc(sizeof(char*) * 10);

	while(1){ // boucle infinie pour être toujours en attente
//lire la ligne
		int cas_gal = 0;
		fgets(ligne, 100 , stdin);
		//TEST printf("j'ai pris note, je vais executer %s \n", ligne); //%s",buff);

// découpage en mots
		char * mot_temp;
		int i=0; // nb de mots
		mot_temp = strtok(ligne," \n");//decoupeMots(ligne);
		while (mot_temp!=NULL && strlen(mot_temp)!=0 && i<10){
			if (!strcmp(mot_temp,"\n")){
				i=9;
			}
			mots[i]=malloc(sizeof(char)*(1+strlen(mot_temp)));
			mots[i]=mot_temp;
			//TEST
			printf("le mot %d est %s\n",i,mots[i]);
			i++;
			mot_temp = strtok(NULL, " \n");
			cas_gal = 1;
		}

		//printf("%d\n", i );

		//if (strcmp(*mots[0],"cd")){
			//printf("il s'agit d'un cd\n");
		//	cd()
		//}
//cas particuliers TODO
		char ** cmd1;
		cmd1 = malloc(sizeof(char*) * 10 );
		for (int j=0; j<i;j++){
			if (!(strcmp(mots[j],"|") && strcmp(mots[j],">") && strcmp(mots[j],">>") && strcmp(mots[j],"<")) ){
					//TEST										printf("il s'agit d'une redirection\n");
					cas_gal=0;
					char ** cmd2;
					cmd2 = malloc(sizeof(char*) * (i-j));
					for(int k=j+1;k<i;k++){
						cmd2[k-j-1]=malloc(sizeof(char)*(1+strlen(mots[k])));
						cmd2[k-j-1]=mots[k];
					}
					Red(mots[j], cmd1, cmd2);
					wait(NULL);
					//TEST
					 printf("DONE\n");
					free (cmd2);
					printf("PATH > ");//TODO %S €",$PATH);
					break;
			}else {
				cmd1[j]=malloc(sizeof(char)*(1+strlen(mots[j])));
				cmd1[j] = mots[j];
			}
		}
		free (cmd1);

		if (cas_gal){
//cas général
			if (!fork()){ //c'est le fils qui exécute la commande
				//TEST printf("je suis au point d'exécution, je vais exécuter %s\n", mots[0] );
				execvp(mots[0],mots);//arg);
				exit(1); //on ne revient pas d'un exec
			}
			wait(NULL);
			printf("PATH > ");//TODO %S €",$PATH);
			cas_gal=0;
		}
		free(ligne);
		free(mots);
		ligne = malloc(sizeof(char) * 100);
		mots = malloc(sizeof(char*) * 10);


//gestion du CRTL^C
	//if SIGINT free tout
	}
	//remise à zéro
			free(ligne);
			free(mots);
  return 0;
}
