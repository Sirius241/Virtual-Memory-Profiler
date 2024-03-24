#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);

    // Construct `/proc/{pid}/status` path
    char proc_status_file[32];
    sprintf(proc_status_file, "/proc/%d/status", pid);

    FILE *fp = fopen(proc_status_file, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[128];
    long vmsize = 0, rss = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "VmSize: %ld kB", &vmsize) == 1) {
            break;
        } else if (sscanf(line, "VmRSS: %ld kB", &rss) == 1) {
            break;
        }
    }
    int page_faults = 0;
    char line1[128]; 
    while (fgets(line, sizeof(line1), fp) != NULL) {
        if (strstr(line, "majflt:") != NULL) {
            sscanf(line, "majflt: %d", &page_faults);
            break; 
        }
    }

    fclose(fp);
    printf("Virtual memory size: %ld kB\n", vmsize);
    struct rusage usage;
    int err = getrusage(RUSAGE_SELF, &usage);
    if (err == -1) {
        perror("getrusage");
        return 1;
    }

    long heap_max_kb = usage.ru_maxrss * 1024 / 1024;
    struct rlimit stack_limit;
    if (getrlimit(RLIMIT_STACK, &stack_limit) == -1) {
        perror("getrlimit");
        return 1;
    }

    long stack_max_kb = stack_limit.rlim_cur * 1024 / 1024;

    printf("PID: %d\n", pid);
    printf("Peak Heap Usage: %ld kB\n", heap_max_kb);
    printf("Peak Stack Usage: %ld kB\n", stack_max_kb);
    if (page_faults == 0) {
        fprintf(stderr, "Could not find page fault information for PID %d\n", pid);
        return 1;
    }

    printf("PID: %d\n", pid);
    printf("Estimated Page Faults: %d\n", page_faults);

    printf("%d,%ld,%ld,%ld\n", pid, vmsize, heap_max_kb, stack_max_kb);

    return 0;
}

