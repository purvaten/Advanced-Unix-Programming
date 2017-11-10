#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int ret;
    pid_t pid;

    // forking
    if ((pid = fork()) < 0) {
        printf("Fork error\n");
        return 1;
    }
    if (pid == 0) { /* Child */
        printf("In child : trying to kill parent\n");
        ret = kill(getppid(), SIGINT);    // attempting to kill parent
        if (!ret)
            printf("In child : Parent killed successfully!\n");
        else
            printf("In child : Error in killing parent\n");
    }
    else {  /* Parent */
        printf("In parent : going to sleep\n");
        sleep(5);
        printf("In parent : waking up... Exiting!\n");
        exit(0);
    }

    return 0;
}
