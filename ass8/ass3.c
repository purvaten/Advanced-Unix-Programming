#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	pid_t pid;
	int x;
	char cmd1[] = "cat"; char *args1[] = {"cat", "test.txt", NULL};

	pid = fork();
	if (pid < 0) {
		printf("Fork error\n");
		return 1;
	}
	if (pid == 0) {
		/* Child */
		sleep(3);
		printf("Child : Process group ID = %d\n\n", getpgid(0));
		printf("Exec starting...\n");
		execvp(cmd1, args1);
	}
	else {
		/* Parent */
		printf("Parent : Setting Process group ID of child = %d\n", pid);
		setpgid(pid, pid);
		wait(&x);
		printf("\nExec is over...\n");
		x = setpgid(pid, pid);
		if (x == -1)
			printf("Error in setting pgid of child process\n");
	}
	return 0;
}
