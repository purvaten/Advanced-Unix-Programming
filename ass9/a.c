#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void sig_term(int signum) {
    printf("Caught signal %d\n", signum);
}

int main(int argc, char *argv[]) {

    // initialization for sigaction
    struct sigaction act;
    act.sa_handler = sig_term;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGTERM);
    act.sa_flags = 0;

    // register to catch SIGTERM
    sigaction(SIGTERM, &act, NULL);

    // register to ignore SIGINT
    signal(SIGINT, SIG_IGN);

    // register to accept default action for SIGSEGV
    signal(SIGSEGV, SIG_DFL);

    printf("\nPausing... waiting for signal\n");
    pause();
    printf("\nPause ended... leaving\n");

    return 0;
}
