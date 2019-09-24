#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 3

void CountUp() {
    long sum = 0;
    long upper_bound = 100000000;
    for (long i = 0; i < upper_bound; i++) {
        sum += i;
    }
    // does nothing with the result
}

void *PrintOneChar(void *thread_args) {
    while(1) {
        for (int i = 0; i < 10; i++) {
            printf("%d\n", i);
            CountUp();
        }
    }
    pthread_exit(NULL);
}

void *PrintOneLetter(void *thread_args) {
    while(1) {
        for (int i = 0; i < 26; i++) {
            printf("%c\n", (char) 97+i);
            CountUp();
        }
    }
    pthread_exit(NULL);
}

void *PrintOnePound(void *thread_args) {
    while(1) {
        printf("#\n");
        CountUp();
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    
    pthread_t threads[NUM_THREADS];
    int rc;
    void* method_pointer;
    for(int thread_index = 0; thread_index < NUM_THREADS; thread_index++) {
        printf("Creating thread #: %d\n", thread_index);
        if (thread_index == 0) {
            method_pointer = PrintOneChar;
        }
        else if (thread_index == 1) {
            method_pointer = PrintOneLetter;
        }
        else { 
            method_pointer = PrintOnePound;
        }
        rc = pthread_create(&threads[thread_index], NULL, method_pointer, NULL);
        if (rc) {
            printf("ERROR from pthread_create() with code: %d\n", rc);
            exit(-1); 
        }   
    }

    pthread_exit(NULL);
}

