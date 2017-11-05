#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char *vec[3];
	if (argc < 2) {
		printf("Please type a file name.\n");
		return 1;
	}

	vec[0] = "/bin/cat"; vec[1] = argv[1]; vec[2] = 0;
	if (execve(vec[0], vec, 0) < 0) {
		printf("exec error\n");
		return 0;
	}

	return 0;
}
