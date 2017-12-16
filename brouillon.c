//redirection de l'entrée standard sur l'entrée d'un pipe
      int fd[2];
      pipe(fd);
      dup2(fd[1],1);

  scanf("%s\n", &buff );


char *buff=NULL;
ssize_t bufsize=0;
getline(&buff, &bufsize, stdin);


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
