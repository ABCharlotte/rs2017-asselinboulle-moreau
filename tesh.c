#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main() {
	printf("pour arrêter le tesh il faut faire CRTL^C\n");
	
	//redirection de l'entrée standard sur l'entrée d'un pipe 
	int fd[2]; 
	pipe(fd); 
	dup2(fd[1],1);	
	//buffer de stockage de l'entrée : on considère qu'une ligne de commande fait moins de 1000 caractères 
	char buff[1000];
	while(1){ // boucle infinie pour être toujours en attente
		write(fd[0],buff,2);
		int i=1;
		//tant que les 2 derniers caractères ne sont pas le caractère d'échappement de la touche entrée on écrit la sortie du pipe dans le buff
		while(buff[i-1]!="\\" && buff[i]!="r"  ){  //strcmp(buff[i-1,i],"\r")){
			i++;
			write(fd[0],buff[i],1); 
		}
		printf("%s",*buff);
// TODO : il va falloir faire le découpage des mots ici et puis analyser les cas particuliers x') 
//RIP 

		if (!fork()){ //c'est le fils qui exécute la commande 			
//			exec();
			exit(1); //on ne revient pas d'un exec
		} 
		wait(); 
//TODO remise à zéro du buffer
	}
    return 0;
}


