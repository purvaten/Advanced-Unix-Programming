#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
	FILE *fp;
	char filename[] = "f1", abcde[] = "abcde";
	int i, fd;

	fp = fopen(filename, "w+");
	if (fp == NULL) {
		printf("An error was encountered while accessing file!\n");
		return -1;
	}

	for (i = 0; i < 5; i++)
		fputc(abcde[i], fp);
	fclose(fp);

	fd = open("f1", O_WRONLY | O_APPEND);
	lseek(fd, 0, SEEK_SET);
	write(fd, "12345", 5);
	close(fd);

	return 0;
}
