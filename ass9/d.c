#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>

static void my_func(int signum) {
	return;
}

int main() {
	pid_t pid;
	sigset_t newmask, oldmask, pendmask;
	int x;

	signal(SIGINT, my_func);
	signal(SIGALRM, my_func);

	if ((pid = fork()) < 0) {
		printf("Fork error\n");
		return 1;
	}
	else if (pid == 0) {	/* Child */
		printf("In child : starting\n");
		if (sigprocmask(SIG_SETMASK, NULL, &oldmask) < 0) {
			printf("sysblock err\n");
			return 1;
		}

		// printing mask
		if (sigpending(&pendmask) < 0) {
			printf("sigpending error\n");
			return 1;
		}

		x = sigismember(&oldmask, SIGINT);
		if (x)
			printf("SIGINT is pending in child\n");
		else
			printf("SIGINT is NOT pending in child\n");

		printf("Setting alarm - try SIGINT to verify in the next 5 secs\n");
		alarm(5);
		pause();
		printf("\nIn child : leaving\n");
	}
	else {	/* Parent */
		// change sigprocmask
		printf("In Parent : started and waiting for child\n");
		sigemptyset(&newmask);
		sigaddset(&newmask, SIGINT);
		if (sigprocmask(SIG_SETMASK, &newmask, NULL) < 0) {
			printf("sysblock err_sys\n");
			return 1;
		}

		wait(&x);

		printf("In parent : SIGINT has been blocked - verify this in the next 5 secs\n");
		alarm(5);
		pause();
		printf("\nIn parent : leaving\n");
	}

	return 0;
}
