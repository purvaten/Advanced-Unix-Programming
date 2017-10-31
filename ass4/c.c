#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#define N 10

double get_time_difference(struct timeval start, struct timeval end) {
	return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}

double time_getpid() {
	printf("getpid() function calls...\n");
	struct timeval getpid_start;
	struct timeval getpid_end;
	double sum_getpid_times_elapsed = 0.0;
	pid_t pid;
	int i;

	for(i = 0; i < N; i++){
		gettimeofday(&getpid_start, NULL);
		pid = getpid();
		gettimeofday(&getpid_end, NULL);
		sum_getpid_times_elapsed += get_time_difference(getpid_start, getpid_end);
		printf("%d - %lf\n", i, get_time_difference(getpid_start, getpid_end));
	}
	return sum_getpid_times_elapsed / 10;
}

double time_fork() {
	printf("fork() function calls...\n");
	struct timeval fork_start;
	struct timeval fork_end;
	double sum_fork_times_elapsed = 0.0;
	int i;

	for (i = 0; i < N; i++) {
		gettimeofday(&fork_start, NULL);
		int p = fork();
		gettimeofday(&fork_end, NULL);
		if (p) {
			sum_fork_times_elapsed += get_time_difference(fork_start, fork_end);
			printf("%d - %lf\n", i, get_time_difference(fork_start, fork_end));
		}
		else
			exit(0);
	}
	return sum_fork_times_elapsed / 10;
}


int main(){
	printf("--------------------------------------\n");
	printf("AVERAGE TIME FOR getpid() - %lf\n", time_getpid());
	printf("--------------------------------------\n");
	printf("AVERAGE TIME FOR fork() - %lf\n", time_fork());
	printf("--------------------------------------\n");
	return 0;
}