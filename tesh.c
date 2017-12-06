#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


//fonction replacée par strtok
char ** decoupeMots(char* ligne){
	int i=0; // nb de mots
	char** sortie;
	char* temp=malloc(sizeof(char)*64);
	int l=0;
	for(int j=0; j<strlen(ligne); j++){
		printf("on compare à espace :%s\n",&ligne[j] );
		if(ligne[j]!=' '){
			printf("lel %d %d\n",i,j );
			temp[l]=ligne[j];
			l++;
		}else{ // si c'est un espace je "crée" un nouveau mot
			sortie[i]=temp;
			temp="";
			printf("%s\n", &sortie[i] );
			l=0;
			i++;
		}
	}
	free(temp);
	return sortie;
}


int main() {
	printf("pour arrêter le tesh il faut faire CRTL^C\n");
	printf("PATH € ");//TODO %S €",$PATH);
//ligne = buffer stockage de l'entrée : on considère qu'une ligne de commande fait moins de 1000 caractères
	char *ligne;
	ligne = malloc(sizeof(char) * 100);
	char  **mots;
// les mots : on considère qu'il y en a max 10
	mots = malloc(sizeof(char*) * 10);
	while(1){ // boucle infinie pour être toujours en attente

		fgets(ligne, 100 , stdin);
		printf("j'ai pris note, je vais executer %s \n", ligne); //%s",buff);

// découpage en mots
		char * mot_temp;
		int i=0; // nb de mots
		mot_temp = strtok(ligne," ");//decoupeMots(ligne);
		while (mot_temp!=NULL && strlen(mot_temp)!=0 && i<10){
			mots[i]=malloc(sizeof(char)*(1+strlen(mot_temp)));
			mots[i]=mot_temp;
			printf("le mot %d est %s\n",i,mots[i]);
			i++;
			mot_temp = strtok(NULL, " ");
		}

		//cas particuliers TODO

//cas général
		if (!fork()){ //c'est le fils qui exécute la commande
			printf("je suis au point d'exécution\n" );
			execvp(mots[0],mots);//arg);
			exit(1); //on ne revient pas d'un exec
		}
		wait(NULL);

		printf("PATH € ");//TODO %S €",$PATH);
//gestion du CRTL^C
	//if SIGINT free tout
	}
	//remise à zéro
			free(ligne);
			free(mots);
  return 0;
}
