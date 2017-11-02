#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	char *filename = argv[1], buffer1[] = "parent", buffer2[] = "child";

	int fd, pid = fork();

	if (pid == 0) {
		fd = open(filename , O_CREAT | O_WRONLY | O_TRUNC);
		if(fd == -1) {
			perror("Error");
			exit(1);
		}
		printf("\nWriting \"%s\" to file \"%s\" in parent process...\n\n", buffer1, filename);
		write(fd, buffer1, strlen(buffer1));
		wait(0);
	}
	else {
		printf("\nWriting \"%s\" to file \"%s\" in child process...\n\n", buffer2, filename);
		write(fd, buffer2, strlen(buffer2));
		printf("\n");
	}
	close(fd);
	return 0;
}
