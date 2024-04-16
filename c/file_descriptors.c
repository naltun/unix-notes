/**
 *
 *      --== F I L E  D E S C R I P T O R S ==--
 *
 *
 *
 * tl;dr - compile and run with:
 *
 *      $ cc file_descriptors.c && ./a.out
 *
 *
 *
 * A Unix file descriptor is a positive integer that uniquely identifies an open file. Since "Everything
 * Is A File" (TM) in Unix, file descriptors also identify Unix pipes and sockets. This identifier is
 * managed by the kernel to track files for input/output procedures, such as printing text to a terminal
 * or writing a buffer of bytes to a file.
 *
 * In example, `file_descriptors.c' has a unique descriptor as I am editing the file (since it is opened).
 * File descriptor is often shortened to `fd'.
 *
 * The kernel manages all FDs via a process' `file descriptor table'. Additionally, the kernel manages
 * all system files via the `file table', which is used to index all files across the system. Whereas
 * the file table exposes system files to processes, the file descriptor table is used to store file
 * descriptors that a process requires. This allows the process to more easily perform I/O operations
 * on the correct file.
 *
 * Unix has a number of default file descriptors: standard output, standard input, and standard error.
 * These FDs are used to handle text streams, and are abbreviated as stdin, stdout, and stderr
 * respectively. These FDs are hard coded as the following:
 *
 *      stdin  = 0
 *      stdout = 1
 *      stderr = 2
 *
 * Let's write a simple program to demonstrate how file descriptors work. We will inspect the stdout
 * and stderr file descriptors alongside 3 files managed by a userspace process (this program!).
 * files managed by a userspace process (this program!).
 *
 * Review the output and answer the following:
 * - What are the FDs for stdout and stderr?
 * - What are the FDs for the 3 temporary files?
 * - Based on what you've learned, why do you think the temporary file FDs are as they are?
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <stdio.h> // fprintf(3), printf(3)
#include <unistd.h> // fileno(3)

int main() {
    char *foo, *bar, *baz;
    FILE *fp_foo, *fp_bar, *fp_baz; // File pointers to the entries in the file table

    foo = "/tmp/foo";
    bar = "/tmp/bar";
    baz = "/tmp/baz";

    printf("Let's look at stdout and stderr...\n");
    fprintf(stdout, "Hello from stdout! FD: %d\n", fileno(stdout));
    fprintf(stderr, "Hello from stderr! FD: %d\n\n", fileno(stderr));

    printf("Let's create 3 temporary files, `%s', `%s', and `%s', open them,"
            " and examine their FDs...\n", foo, bar, baz);

    fp_foo = fopen(foo, "w");
    fp_bar = fopen(bar, "w");
    fp_baz = fopen(baz, "w");

    printf("FD for %s: %d\n", foo, fileno(fp_foo));
    printf("FD for %s: %d\n", bar, fileno(fp_bar));
    printf("FD for %s: %d\n", baz, fileno(fp_baz));

    fclose(fp_foo);
    fclose(fp_bar);
    fclose(fp_baz);

    return 0;
}
