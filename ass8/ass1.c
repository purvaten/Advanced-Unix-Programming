/* Implementing - wait2 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>

pid_t wait2(int *wtime, int *rtime, int *iotime) {
	pid_t child;
	struct tms buf;
	int status;

	child = wait(&status);
	times(&buf);

	*wtime = (int)(buf.tms_cstime);
	*rtime = (int)(buf.tms_cutime);
	*iotime = *wtime - *rtime;

	return child;
}

int main(int argc, char *argv[]) {
	pid_t pid;
	int x, wtime, rtime, iotime, i;
	char cmd1[] = "ls"; char *args1[] = {"ls", "-l", NULL};

	pid = fork();
	if (pid < 0) {
		printf("Fork error\n");
		return 1;
	}
	if (pid == 0) {
		/* Child */
		for (i = 0; i < 100000; i++)
			printf("Printing in child for loop\n");
		execvp(cmd1, args1);
	}
	else {
		/* Parent */
		x = wait2(&wtime, &rtime, &iotime);
		if (x == -1) {
			printf("wait2 failure\n");
			return 1;
		}

		printf("wtime = %d, rtime = %d, iotime = %d\n", wtime, rtime, iotime);
	}
	return 0;
}
