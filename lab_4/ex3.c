#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

static int parse(char *line, char *args[])
{
    int count = 0;
    char *token = strtok(line, " \t\n");
    while (token != NULL && count < MAX_ARGS - 1) {
        args[count++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[count] = NULL;
    return count;
}

static void reap_children(void)
{
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
        printf("[%d] done\n", pid);
}

int main(void)
{
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        reap_children();
        printf("myshell> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        if (parse(line, args) == 0)
            continue;

        if (strcmp(args[0], "exit") == 0)
            break;

        if (strcmp(args[0], "cd") == 0) {
            const char *dir = args[1] ? args[1] : getenv("HOME");
            if (dir == NULL || chdir(dir) != 0)
                perror("cd");
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }
        if (pid == 0) {
            execvp(args[0], args);
            perror("exec");
            exit(EXIT_FAILURE);
        }

        printf("[%d] started in background\n", pid);
    }

    while (wait(NULL) > 0)
        ;
    return EXIT_SUCCESS;
}
