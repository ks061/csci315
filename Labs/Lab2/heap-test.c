#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int* data = (int*) malloc(sizeof(int));
    *data = 99;

    int pid;
    int status;

    if ((pid = fork()) == 0) {
        printf("child -- value of data: %d\n", *data);
    } else {
        printf("parent -- value of data: %d\n", *data);
        wait(&status);
    }

    free(data);
    exit(0);
}
