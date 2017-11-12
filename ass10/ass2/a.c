/* Even */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "ass2.h"

#define BUFFER 4
#define INGOING "OddEven.fifo"

extern int fileptr;

int main(int argc, char *argv[]) {
	int n = 2, x = 0;
    char input[BUFFER]={0};
    mkfifo(INGOING, 0666);

    int fd = open(INGOING, O_RDWR);
    fileptr = open("ass2.txt", O_APPEND | O_WRONLY);

    if (fd == -1) {
        perror("open error");
        return 1;
    }

    while (n <= 100) {
    	sleep(1);
    	while (x != n-1) {
	        if (read(fd, input, BUFFER) == -1) {
	            perror("read error");
	            return 1;
	        }
	        x = atoi(input);
	    }

	    sleep(1);
        sprintf(input, "%d", n);
        if (write(fd, input, strlen(input)) == -1) {
	        perror("write error");
	        return 1;
	    }
        //printf("\nEven : wrote %s\n", input);
        write(fileptr, input, strlen(input));

        n += 2;
    }
    printf("\n");

    close(fileptr);

    return 0;
}
