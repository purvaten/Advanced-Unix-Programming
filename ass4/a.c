#include <stdio.h>
#include <stdlib.h>
#define MAX 	20

extern char **environ;

int main() {
	char name[MAX], val[MAX], **env;

    for (env = environ; *env; ++env)
        printf("%s\n", *env);

    printf("Enter a new env variable and its value\n");
    scanf("%s%s", name, val);
    setenv(name, val, 1);

    for (env = environ; *env; ++env)
        printf("%s\n", *env);

	return 0;
}