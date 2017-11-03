#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

void * myThreadFun(void *i) {
	// do something
	int a = *((int *) i), x;
    free(i);
    x = sched_getcpu();

    printf("Thread %d running on CPU %d...\n", a, x);
    return NULL;
}

int main() {
	int num_proc, i;

	/* Number of processors */
	num_proc = sysconf(_SC_NPROCESSORS_ONLN);
	printf("Number of processors are %d\n", num_proc);

	/* Thread creation */
	pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * num_proc);
	pthread_attr_t attr;
    cpu_set_t cpus;
    pthread_attr_init(&attr);

	for (i = 0; i < num_proc; i++) {
		int *arg = malloc(sizeof(*arg));
        if (arg == NULL) {
            fprintf(stderr, "Couldn't allocate memory for thread arg.\n");
            exit(EXIT_FAILURE);
        }

        *arg = i;
        CPU_ZERO(&cpus);
		CPU_SET(i, &cpus);
        pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpus);
		pthread_create(&tid[i], &attr, myThreadFun, arg);
	}

	for (i = 0; i < num_proc; i++)
		pthread_join(tid[i], NULL);

	return 0;
}