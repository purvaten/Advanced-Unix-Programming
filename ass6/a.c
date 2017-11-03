#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 	20

typedef struct arg_struct {
    int index;
    char word[MAX];
}arg_struct;

int set = 0;

void *myThreadFun(void *arguments) {
	struct arg_struct *args = (arg_struct *) arguments;
    int a = args->index, len_string;
    FILE *fp;
    char filename[MAX], SearchText[MAX], *buffer, *x;
    strcpy(SearchText, args->word);

    /* Opening file */
    sprintf(filename, "%d", a);
    strcat(filename, ".txt");
    fp = fopen(filename, "r");

    /* Searching logic */
	if (fp) {
		fseek (fp, 0, SEEK_END);
		len_string = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		buffer = (char *)malloc(len_string);
		if (buffer)
			fread (buffer, 1, len_string, fp);
		fclose (fp);
	}

	x = strstr(buffer, SearchText); 	// finds first occurence of SearchText in buffer
	if (x != NULL) {
		printf("FOUND in file %d\n", a);
		set = 1;
		exit(0);
	}

    return NULL;
}

int main(int argc, char *argv[]) {
	int i, file_num;
	char word[20];

	if (argc != 3) {
		printf("Invalid number of arguments!\n");
		return -1;
	}

	file_num = atoi(argv[1]);
	strcpy(word, argv[2]);

    pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * file_num);

    /* Threads */
    for (i = 0; i < file_num; i++) {
    	arg_struct *args = (arg_struct *)malloc(sizeof(arg_struct));
    	args->index = i;
    	strcpy(args->word, word);

    	pthread_create(&tid[i], NULL, myThreadFun, (void *)args);
    }

    for (i = 0; i < file_num; i++)
    	pthread_join(tid[i], NULL);

    if (!set)
    	printf("Word not found in any file\n");

    exit(0);
}