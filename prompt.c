#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>

#define taille 1024

void prompt(){
	struct passwd *pwd = getpwuid(getuid());
    char host[taille];
    char *cwd;

    gethostname(host, taille); // récupération hostname
    cwd = getcwd(NULL, 0); // récupération rep courant

    printf("%s@%s:%s$ ", pwd->pw_name, host, cwd); // pwd->pw_name renvoie USER
}
