#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);

    for (int i = 0; i < n; i++) {
        if (fork() < 0) {
            perror("fork");
            return EXIT_FAILURE;
        }
        sleep(5);
    }

    return EXIT_SUCCESS;
}
