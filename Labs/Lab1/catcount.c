#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void print_environment(void) {
    int index = 0;
    while (environ[index] != NULL) {
        printf("%s\n", environ[index]);
        index++;
    }
}

int main(int argc, char* argv[]) {
    
    print_environment();

    if (argc != 2) {
        printf("Incorrect number of arguments!\n");
        exit(-1);
    }

    int status;
    int pid;

    pid = fork();
    if (pid == 0) {
        exit(execlp("/bin/cat", "cat", argv[1], NULL));
    } else {
        wait(&status);
        if (status == 0) {
            pid = fork();
            if (pid == 0) {
                exit(execlp("/usr/bin/wc", "wc", argv[1], NULL));
            } else {
                wait(&status);
                exit(status);
            }
        } else {
            exit(status);
        }
    }

    return 0;
}
