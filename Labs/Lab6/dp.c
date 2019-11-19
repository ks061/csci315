#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define SEC_TO_USEC_FACTOR 1000000

pthread_mutex_t mutex;
pthread_cond_t cond_var;
bool chopstick_available[NUM_PHILOSOPHERS];

void napping(int t, unsigned int* seed) {
    int sleep_utime = (int) (((double)rand_r(seed) / RAND_MAX) * t * SEC_TO_USEC_FACTOR);
    usleep(sleep_utime);
}

int pickup_forks(int id) {
    pthread_mutex_lock(&mutex);
    while (!chopstick_available[id] || !chopstick_available[(id+1) % NUM_PHILOSOPHERS])
        pthread_cond_wait(&cond_var, &mutex);    
    chopstick_available[id] = false;
    chopstick_available[(id+1) % NUM_PHILOSOPHERS] = false;
    pthread_mutex_unlock(&mutex);
    return 0;
}

int return_forks(int id) {
    pthread_mutex_lock(&mutex);
    chopstick_available[id] = true;
    chopstick_available[(id+1) % NUM_PHILOSOPHERS] = true;
    pthread_cond_signal(&cond_var);
    pthread_mutex_unlock(&mutex);
    return 0;
}

void* Philosopher(void* param) {
    int id = (intptr_t) param;
    unsigned int init_seed_value = (uintptr_t) param;
    unsigned int* seed = (unsigned int*) &init_seed_value;
    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        napping(2, seed);
        printf("Philosopher %d is hungry.\n", id);
        pickup_forks(id);
        printf("Philosopher %d is starting to eat.\n", id);
        napping(1, seed);
        printf("Philosopher %d is done eating.\n", id); 
        return_forks(id);
    }
}

int main(int argc, char* argv[]) {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);

    int i;
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        chopstick_available[i] = true;
    }

    pthread_t tid[NUM_PHILOSOPHERS];
    int j;
    for (j = 0; j < NUM_PHILOSOPHERS; j++) {
        pthread_create(&tid[j], NULL, Philosopher, (void*) (intptr_t) j);        
    }
    sleep(15);
    return 0;
}
