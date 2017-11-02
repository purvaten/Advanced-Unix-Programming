#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int pid, sleep_time, process, i;
	process = atoi(argv[1]);
	sleep_time = atoi(argv[2]);

	printf("Creating %d children.\n", process);
	for (i = 0; i < process; i++){
		pid = fork();
		if (pid == 0) {
			printf("Sleeping\n");
			sleep(sleep_time);
			exit(0);
		}
		else if (pid != -1) {
			printf("pid : %d \n", pid);
			waitpid(pid - 1, NULL, 0);
		}
		else
			printf("Error in fork \n");
	}
	wait(0);
	printf("All processes exited. \n");

	return 0;
}
