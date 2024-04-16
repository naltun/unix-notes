/**
 * 
 *      --== S I G N A L S ==--
 *
 *
 *
 *  tl;dr - compile and run with:
 *
 *      $ cc signals.c && ./a.out
 *
 *
 *
 * A Unix signal (aka `software interrupt') is a form of inter-process communication (ICP) that informs
 * a process of an event. With `signal handlers', a process can respond to these notifications based
 * on the signal type. Let's look at an example, ctrl+c:
 *
 *      # Run a program within a Unix environment
 *      $ ./script.sh
 *      some
 *          example
 *              output^C  # Notice ctrl+c
 *      $ echo $?
 *      130  # <-- The exit status from the process is 130
 * 
 * ctrl+c is one signal type and is used to send an interrupt signal (SIGINT) to a running process.
 * SIGINT is used to inform a process to interrupt its normal procedure and cease running, but with
 * a signal handler we can catch and modify this default behavior. Another common signal is ctrl+z,
 * which is used to inform a process to suspend itself (which can be brought back with the `fg' command).
 *
 * signal(2) is used to catch and handle signals by type. According to the Linux man-pages 6.7:
 *
 *      sighandler_t signal(int signum, sighandler_t handler);
 *
 * This means that we can use the signal() function by passing in an int `signum' the handler to
 * when `signum' is caught register. The signal handler is the user's C function that is invoked.
 *
 * Across various Unix systems, `signum' might vary. To enable portability, signal macros like SIGINT
 * are used.
 * 
 * Let's write a simple program to demonstrate handling a an interrupt signal. Compile this file
 * with `cc signals.h'. Run `./a.out' follow the prompt: what is the exit status?
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <signal.h> // signal(2), SIGINT
#include <stdio.h> // printf(3)
#include <stdlib.h> // exit(3), EXIT_SUCCESS
#include <unistd.h> // pause(2)

// Signal handler for SIGINT
void signal_handler(int signum) {
    printf("\n....  Inside the signal handler 🥳"
           "\n....  The value of `signum' is: %d"
           "\n....  Make sure to `echo $?' ✅\n", signum);

    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    // Use signal(2) to catch and handle SIGINT by invoking signal_handler()
    signal(SIGINT, signal_handler);

    printf("Press ctrl+c to catch SIGINT\n");
    while (1) {
        // Make the process sleep until a signal is received
        pause();
    }

    return 0;
}
