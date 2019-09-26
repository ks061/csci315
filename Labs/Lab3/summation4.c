/*
 * Copyright (c) 2012 Bucknell University
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

// structure for thread arguments
struct thread_args {
	int tid;
	int a;
	int b;
	double x;
	double result;
};

struct timeval* calc_time_diff(struct timeval* start_time, struct timeval* end_time) {
	struct timeval* summed_time = (struct timeval*) malloc(sizeof(struct timeval));
        if (end_time->tv_usec < start_time->tv_usec) {
            end_time->tv_sec -= 1;
            end_time->tv_usec += 1000000;
        }
        summed_time->tv_sec = end_time->tv_sec - start_time->tv_sec;
        summed_time->tv_usec = end_time->tv_usec - start_time->tv_usec;
        return summed_time;
}

extern int shared;

// function that each thread will execute
void *SumExp(void *args_ptr) {
        struct timeval* start_time = (struct timeval*) malloc(sizeof(struct timeval));
        struct timeval* end_time = (struct timeval*) malloc(sizeof(struct timeval));
        gettimeofday(start_time, NULL);	

        int i;
	struct thread_args *myargs_ptr = (struct thread_args*) args_ptr;
	myargs_ptr->result = 0;

	shared = 123;

	printf("Thread %d starting a= %d, b= %d, x= %lf\n",
			myargs_ptr->tid,
			myargs_ptr->a,
			myargs_ptr->b,
			myargs_ptr->x);

	for (i=myargs_ptr->a; i<myargs_ptr->b; i++) {
		myargs_ptr->result += pow(i, myargs_ptr->x);
                // if ((myargs_ptr->tid) == 0) exit(-1); // exits if thread 0
                // if ((myargs_ptr -> tid) == 0) execl("/bin/ls","/bin/ls",".",NULL);
	}

	printf("Thread %d done a= %d, b= %d, x= %lf -> result = %lf\n",
			myargs_ptr->tid,
			myargs_ptr->a,
			myargs_ptr->b,
			myargs_ptr->x,
			myargs_ptr->result);

        gettimeofday(end_time, NULL);

        struct timeval* summed_time = calc_time_diff(start_time, end_time);
        printf("Thread #%d took %d.%d seconds to execute\n", myargs_ptr->tid, (int)summed_time->tv_sec, (int)summed_time->tv_usec);
        free(start_time);
        free(summed_time);
         
        char buffer[100];
        ctime_r(&(end_time->tv_sec), buffer);
        printf("Thread #%d terminated at %s", myargs_ptr->tid, buffer);
        free(end_time);

	pthread_exit((void*) args_ptr);
}

int shared;

int main (int argc, char *argv[]) {

        struct timeval* start_time = (struct timeval *) malloc(sizeof(struct timeval));
        struct timeval* end_time = (struct timeval *) malloc(sizeof(struct timeval));
        gettimeofday(start_time, NULL);
	pthread_attr_t attr;

	struct thread_args *targs; // array for thread argument structs
	struct thread_args **tstatus; // array of pointers to returns from threads
	pthread_t *tidp; // array for thread ids

	int ret_val;
	int i;
	// void *status;
	double summation = 0;

	int num_threads, increment; // command line parameters

	if (argc < 3) {
		printf("usage: summation [numthreads] [increment]\n");
		exit(-1);
	}

	num_threads = atoi(argv[1]);
	increment = atoi(argv[2]);

	targs = (struct thread_args *) calloc(num_threads, sizeof(struct thread_args));
	tstatus = (struct thread_args **) calloc(num_threads, sizeof(struct thread_args *));
	tidp = (pthread_t *) calloc(num_threads, sizeof(pthread_t));

	// initialize attr variable
	pthread_attr_init(&attr);

	// initialize thread detached state to joinable
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (i=0; i<num_threads; i++) {
		tstatus[i] = malloc(sizeof(struct thread_args));

		targs[i].a = increment*i;
		targs[i].b = increment*(i+1);
		targs[i].x = 2;
		targs[i].tid = i;
		targs[i].result = 0;

		ret_val = pthread_create(&tidp[i], &attr, SumExp, (void *) &targs[i]);
		if (ret_val) {
			printf("ERROR in pthread_create for thread %d: return value= %d\n", 
					i, ret_val);
			exit(-1);
		}
	}

	// free attribute variable
	pthread_attr_destroy(&attr);

	// main thread waits for spawned threads to terminate
	for(i=0; i<num_threads; i++) {
		// 
		ret_val = pthread_join(tidp[i], (void **) &tstatus[i]);
		if (ret_val) {
			printf("ERROR in pthread_join() for thread %d = return value= %d\n",
					i, ret_val);
			exit(-1);
		}

		summation += tstatus[i]->result;
		printf("Joined thread %d; returned= %lf\n", i, tstatus[i]->result);
	}

	printf("Total value computed = %lf\n", summation);
	
        gettimeofday(end_time, NULL);
        struct timeval* summed_time = calc_time_diff(start_time, end_time);
        printf("Program execution time: %d.%d seconds\n", (int) summed_time->tv_sec, (int) summed_time->tv_usec);
        free(start_time);
        free(end_time);
        free(summed_time);        

        pthread_exit(NULL);
	printf("still here\n");
}
