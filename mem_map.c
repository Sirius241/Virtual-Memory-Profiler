#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void check_memory_maps(pid_t pid) {
    char command[128];
    FILE *fp;

    sprintf(command, "cat /proc/%d/maps", pid);

    fp = popen(command, "r");
    if (!fp) {
        perror("popen");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("Memory Mapping Information (PID %d):\n%s", pid, line);
    }

    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);

    check_memory_maps(pid);
    return 0;
}
