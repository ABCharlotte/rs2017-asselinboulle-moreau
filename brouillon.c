//redirection de l'entrée standard sur l'entrée d'un pipe
      int fd[2];
      pipe(fd);
      dup2(fd[1],1);

  scanf("%s\n", &buff );


char *buff=NULL;
ssize_t bufsize=0;
getline(&buff, &bufsize, stdin);
