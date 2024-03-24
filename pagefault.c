#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_page_faults(pid_t pid) {
    struct rusage usage;
    if (getrusage(RUSAGE_CHILDREN, &usage) != 0) {
        perror("getrusage");
        return;
    }
    
    printf("Page faults (minor): %ld\n", usage.ru_minflt);
    printf("Page faults (major): %ld\n", usage.ru_majflt);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        execvp(argv[1], &argv[1]);
        perror("execvp");
        return EXIT_FAILURE;
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }

        print_page_faults(pid);

        return EXIT_SUCCESS;
    }
}
