#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define NAME_MAX 50

int main() {
	char buf[NAME_MAX];
	int fd1 = open("text.txt", O_RDONLY);
	int c;
	if((c = read(fd1, buf, NAME_MAX)) < 0) {
		printf("read error\n");
		return 0;
	}
	if(buf[c - 1] == '\n')
		buf[c - 1] = '\0';
	else
		buf[c] = '\0';

	int pid;
	char *arg[2];
	arg[0] = buf;
	arg[1] = NULL;
	char cmd[NAME_MAX] = "./";
	strcat(cmd, buf);

	pid = fork();
	if (pid == 0) {
		if(execvp(cmd, arg) == -1) {
			printf("error\n");
			exit(0);
		}
	}

	return 0;
}
