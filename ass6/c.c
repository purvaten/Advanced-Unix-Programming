#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 	20

typedef struct arg_struct {
    int index;
}arg_struct;

int set = 0;

void *myThreadFun(void *arguments) {
	struct arg_struct *args = (arg_struct *) arguments;
    int a = args->index;

    printf("Thread ID : %d\n", a);

    return NULL;
}

int main(int argc, char *argv[]) {
	int i;

    pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * 5);

    /* Threads */
    for (i = 0; i < 5; i++) {
    	arg_struct *args = (arg_struct *)malloc(sizeof(arg_struct));
    	args->index = i;

    	pthread_create(&tid[i], NULL, myThreadFun, (void *)args);
    }

    for (i = 0; i < 5; i++)
    	pthread_join(tid[i], NULL);

    return 0;
}