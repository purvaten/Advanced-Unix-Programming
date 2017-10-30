#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 	100

int main(int argc, char *argv[]) {
	int fd;
	FILE *fp;
	char string[MAX];

	if (argc != 3) {
		printf("Invalid number of arguments\n");
		return 1;
	}

	fp = fopen(argv[1], "w+");
	fd = open(argv[2], O_CREAT | O_WRONLY);

	/* Writing stdin to file */
	scanf("%s", string);
	fprintf(fp, "%s\n", string);
	fclose(fp);

	/* Redirecting stdout */
	close(1);
	dup(fd);
	close(fd);
	printf("%s\n", string);

	return 0;
}