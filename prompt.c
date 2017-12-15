#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>

#define taille 1024

int prompt(){
	struct passwd *pwd = getpwuid(getuid());
    char host[taille];
    char *cwd;

    gethostname(host, taille);
    cwd = getcwd(NULL, 0);

    printf("%s@%s %s\n", pwd->pw_name, host, cwd);

    return 0;
}