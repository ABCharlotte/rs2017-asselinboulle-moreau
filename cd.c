#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>

char *dir;
int errno;

void Cd(char **mot){
    char *cwd;
	if ((strcmp(mot[0], "cd")) == 0 ) {
 
        if ((strcmp(mot[1], "~")) == 0){
            dir = getenv("HOME");
        }else{
            dir = argv[1];
 		}

        int t = chdir(dir);
 
        if (t < 0){
            printf("\nDirectory change failed : %s\n",strerror(errno));
        } 
	}
}