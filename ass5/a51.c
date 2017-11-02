//A child process inherits real user id, real group id, effective user id and effective group id of the parent process, while process id and parent process id are not. Demonstrate.
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
	pid_t child_pid = fork();
	if (child_pid == 0) {
		printf("Parent :-\nruid: %d\trguid: %d\teuid: %d\teguid: %d\tpid: %d\tppid: %d\n\n",
			getuid(), getgid(), geteuid(), getegid(), getpid(), getppid());
		wait(0);
	}
	else
		printf("Child :-\nruid: %d\trguid: %d\teuid: %d\teguid: %d\tpid: %d\tppid: %d\n\n",
			getuid(), getgid(), geteuid(), getegid(), getpid(), getppid());

	return 0;
}
