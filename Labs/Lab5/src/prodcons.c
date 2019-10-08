/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "circular-list.h" 

/* SCALE_FACTOR is a constant for you to experiment with:
 * if you choose a very large SCALE_FACTOR, your threads
 * might spend a long time sleeping. If you choose it to be
 * too small, your threads will not sleep at all. Note
 * that in the producer and consumer functions, the sleep
 * time is computed as the INTEGER DIVISION below:
 *
 *  usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX
 *
 *  where RAND_MAX is the largest random numver returned
 *  by rand_r. If the numerator is smaller than RAND_MAX,
 *  the quotient of the integer division is ZERO!
 */
#define SCALE_FACTOR 1000

// global variables -----------------------

struct circular_list mylist;

// end of global variables ----------------

void *producer (void *param) {
  item i;
  unsigned int seed = 1234;
 
  // init mutex
  while (true) {
    // sleep for random period of time
    usleep(SCALE_FACTOR * ((double)rand_r(&seed) / RAND_MAX)); 
    
    // generate a random number
    i = (item) (((double) rand_r(&seed)) / RAND_MAX);
    
    if (circular_list_insert(&mylist, i) == -1) {
      printf("PRODUCER: error condition\n");
    } else {
      printf("PRODUCER: produced value %lf\n", i);
    }
  }
}

void *consumer (void *param) {
  item i;
  unsigned int seed = 999;

  while (true) {
    // sleep for random period of time
    usleep(SCALE_FACTOR * ((double)rand_r(&seed) / RAND_MAX)); 

    if (circular_list_remove(&mylist, &i) == -1) {
      printf("CONSUMER: error condition\n");
    } else {
      printf("CONSUMER: consumed value %lf\n", i);
    }
  }
}

int main (int argc, char *argv[]) {
  int num_prod;
  int num_cons;
  int sleep_time;  
  
  if (argc == 4) {
      // get command line arguments
      num_prod = atoi(argv[1]); // number of producer thread(s)
      num_cons = atoi(argv[2]); // number of consumer thread(s)
      sleep_time = atoi(argv[3]); // number of seconds to sleep before process terminates  
  } else {
      // if error in command line argument usage, terminate with helpful
      // message
      printf("Error: please specify exactly three arguments.\n");
      printf("./prodcons [num_prod] [num_cons] [sleep_time]\n");
      printf("[num_prod] is the number of producer threads\n");
      printf("[num_cons] is the number of consumer threads\n");
      printf("[sleep_time] is the number of seconds to sleep before the process terminates\n");
      exit(-1);
  }
  
  // initialize buffer
  circular_list_create(&mylist, 20);
  
  int num_threads_created = 0;
  pthread_t tid; // thread id
  
  // populate seed values
  int seed_values[num_prod + num_cons];
  for (int i = 0; i < num_prod + num_cons; i++) {
      seed_values[i] = i;
  }

  // create producer thread(s)
  for ( ; num_threads_created < num_prod; num_threads_created++) {
      if (pthread_create(&tid, NULL, producer, (void*)&seed_values[num_threads_created]) == 0) continue;
      else printf("Error: could not create producer thread (thread #%li).\n", (unsigned long int) tid);
  }
  
  // create consumer thread(s)
  for ( ; num_threads_created < num_prod + num_cons; num_threads_created++) {
      if (pthread_create(&tid, NULL, consumer, (void*)&seed_values[num_threads_created]) == 0) continue;
      else printf("Error: could not create consumer thread (thread #%li).\n", (unsigned long int) tid);
  }  

  // sleep to give time for threads to run
  sleep(sleep_time);

  // exit
  return (0);
}
