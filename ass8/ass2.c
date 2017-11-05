#include <stdio.h>
#include <unistd.h>

int main() {
	pid_t child, sess_id;
	FILE *fp;

	child = fork();
	if (child < 0) {
		printf("Fork error\n");
		return 1;
	}
	if (child == 0) {
		/* Child */
		sess_id = setsid();
		printf("Session leader : %d\n", sess_id);
		fp = fopen("/dev/tty", "r");
		if (fp == NULL)
			printf("Process does not have controlling terminal\n");
	}
	else {
		/* Parent */
		printf("Child ID : %d\n", child);
	}
	return 0;
}
