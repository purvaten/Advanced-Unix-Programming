#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE		50

int main() {
	pid_t child_a, child_b;
	int fd1[2], fd2[2], fd3[2], fd4[2];
	int n;
	char line[MAXLINE];

	/* Creating pipes */
	if ((pipe(fd1) < 0) || (pipe(fd2) < 0) || (pipe(fd3) < 0) || (pipe(fd4) < 0)) {
		printf("Pipe error\n");
		return 1;
	}

	if ((child_a = fork()) < 0) {
		printf("Fork error\n");
		return 1;
	}
	if (child_a == 0) {		/* Child A */
		/* PATH 1 - receive */
		close(fd1[1]);
		n = read(fd1[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);

		/* PATH 2 - send */
		close(fd2[0]);
		write(fd2[1], "\nDelhi\n", 7);

		/* PATH 3 - send */
		close(fd3[0]);
		write(fd3[1], "\nChennai\n", 9);
	}
	else {
		if ((child_b = fork()) < 0) {
			printf("Fork error\n");
			return 1;
		}
		if (child_b == 0) {		/* Child B */
			/* PATH 3 - receive */
			close(fd3[1]);
			n = read(fd3[0], line, MAXLINE);
			write(STDOUT_FILENO, line, n);

			/* PATH 4 - send */
			close(fd4[0]);
			write(fd4[1], "\nCochin\n", 8);
		}
		else {		/* Parent */
			/* PATH 1 - send */
			close(fd1[0]);
			write(fd1[1], "\nMumbai\n", 8);

			/* PATH 2 - receive */
			close(fd2[1]);
			n = read(fd2[0], line, MAXLINE);
			write(STDOUT_FILENO, line, n);

			/* PATH 4 - receive */
			close(fd4[1]);
			n = read(fd4[0], line, MAXLINE);
			write(STDOUT_FILENO, line, n);

			/* wait for all children to terminate */
			wait(NULL);
		}
	}

	return 0;
}
