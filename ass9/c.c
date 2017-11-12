#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <setjmp.h>

static jmp_buf env_alrm;

static void sig_alarm(int signo) {
	longjmp(env_alrm, 1);
}

unsigned int my_sleep(unsigned int nsecs) {
	/* Returns 0 or the number of unslept seconds */

	int t1, set = 0, ret, old = 0;
	__sighandler_t old_disposition;

	old_disposition = signal(SIGALRM, sig_alarm);
	if (old_disposition == SIG_ERR)
		return(nsecs);

	if (setjmp(env_alrm) == 0) {
		t1 = alarm(nsecs);		// start timer

		/* If previously set alarm is to go off earlier */
		if ((t1 < nsecs) && (t1 > 0)) {
			signal(SIGALRM, old_disposition);
			printf("Doing older alarm\n");
			alarm(t1);
			pause();			// wait for previously set alarm to complete
			printf("Older alarm is done\n");
			old = 1;
		}
		else if (t1 > nsecs)
			set = 1;

		if (old) {
			signal(SIGALRM, sig_alarm);
			alarm(nsecs - t1);	// resetting our alarm
		}

		pause();			// next caught signal
	}

	ret = alarm(0);		// turn off timer - return unslept time

	/* Resetting disposition */
	signal(SIGALRM, old_disposition);

	/* If previously set alarm is to go off later */
	if (set) {
		printf("Continuing previously set alarm : calling for %d secs\n", t1 - nsecs + ret);
		alarm(t1 - nsecs + ret);
	}

	return(ret);
}

int main() {
	int secs;

	printf("In main : testing my_sleep()\n");
	secs = my_sleep(4);
	printf("In main : sleep complete.. %d secs unslept\n", secs);

	return 0;
}
