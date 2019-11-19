#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define SEC_TO_USEC_FACTOR 1000000

pthread_mutex_t chopstick[NUM_PHILOSOPHERS];

int napping(int t, unsigned int* seed) {
    int sleep_utime = (int) (((double)rand_r(seed) / RAND_MAX) * t * SEC_TO_USEC_FACTOR);
    usleep(sleep_utime);
    return 0;
}

int initialize_mutexes() {
    int i;
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopstick[i], NULL);
    }
    return 0;
}

int destroy_mutexes() {
    int i;
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopstick[i]);
    }
    return 0;
}

void* Philosopher(void* param) {
    int id = (intptr_t) param;
    unsigned int init_seed_value = (uintptr_t) param;
    unsigned int* seed = (unsigned int*) &init_seed_value;
    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        fflush(stdout);
        napping(2, seed);
        printf("Philosopher %d is hungry.\n", id);
        fflush(stdout);
        pthread_mutex_lock(&chopstick[id]);
        pthread_mutex_lock(&chopstick[(id+1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d is starting to eat.\n", id);
        fflush(stdout);
        napping(1, seed);
        printf("Philosopher %d is done eating.\n", id); 
        fflush(stdout);
        pthread_mutex_unlock(&chopstick[id]);
        pthread_mutex_unlock(&chopstick[(id+1) % NUM_PHILOSOPHERS]);
    }
}

int main(int argc, char* argv[]) {
    initialize_mutexes();

    pthread_t tid[NUM_PHILOSOPHERS];
    int i;
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&tid[i], NULL, Philosopher, (void*) (intptr_t) i);        
    }
    sleep(600);
    
    destroy_mutexes();

    return 0;
}
