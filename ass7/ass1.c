#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	char *buf[2];
	int pid, status;
	extern char **environ;
	int fd1 = open("test.txt", O_RDONLY);
	buf[0] = (char *)malloc(10);

	sprintf(buf[0], "%i", fd1);
	buf[1] = NULL;
	fcntl(fd1, F_SETFD, 0);
	printf("Close_on_exec not set\n");
	if ((pid = fork()) == 0)
		if (execve("/home/purva/Desktop/pracs/aup/ass7/a", buf, environ) == -1)
			exit(0);

	pid = wait(&status);
	lseek(fd1, 0, SEEK_SET);
	fcntl(fd1, F_SETFD, 1);
	printf("Close_on_exec set\n");
	if ((pid = fork()) == 0)
		if (execve("/home/purva/Desktop/pracs/aup/ass7/a", buf, environ) == -1)
			exit(0);

	pid = wait(&status);
	return 0;
}