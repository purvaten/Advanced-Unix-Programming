#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[]) {
	struct stat st;
	int fd;
	char timet[20];

	if (argc != 2) {
		printf("Invalid number of arguments\n");
		return 1;
	}
	fd = open(argv[1], O_CREAT | O_RDWR);
	if (stat(argv[1], &st) == 0) {
		strftime(timet, 20, "%H:%M", localtime(&(st.st_atime)));
		printf("ATIME : %s\n", timet);

		strftime(timet, 20, "%H:%M", localtime(&(st.st_mtime)));
		printf("MTIME : %s\n", timet);

		strftime(timet, 20, "%H:%M", localtime(&(st.st_ctime)));
		printf("CTIME : %s\n", timet);
	}

	close(fd);

	return 0;
}