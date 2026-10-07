#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

static void report(const char *name, clock_t start)
{
    clock_t end = clock();
    double ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("%-7s | PID = %d | PPID = %d | execution time = %.3f ms\n",
           name, getpid(), getppid(), ms);
}

int main(void)
{
    clock_t start;

    pid_t child1 = fork();
    start = clock();
    if (child1 < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (child1 == 0) {
        report("Child 1", start);
        exit(EXIT_SUCCESS);
    }

    pid_t child2 = fork();
    if (child2 < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (child2 == 0) {
        start = clock();
        report("Child 2", start);
        exit(EXIT_SUCCESS);
    }

    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);
    report("Main", start);

    return EXIT_SUCCESS;
}
