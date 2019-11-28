/**
 * Allocator File
 *
 * Author: Kartikeya Sharma (ks061@bucknell.edu)
 * Lab 7
 * CSCI 315
 * Prof. Stough
 */

#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <stddef.h>

/**
 * Retrieves a chunk of memory of the inputted size from the system.
 * Initializes one doubly-linked list that keeps track of memory chunks
 * that are available, namely free_list, and one doubly-linked list that
 * keeps track of memory chunks that are already allocated, namely  
 * allocated_list. The chunk of memory received from the system is added
 * to free_list.
 *
 * @param size size of memory chunk to be added to initialized free_list
 *
 * @return 0 if successful; otherwise, -1 if unsuccessful
 */
int allocator_init(size_t size);


/**
 * Allocates a chunk of memory based on the allocation
 * policy set in the alloc_algo variable; the allocation
 * policies include first fit, best fit, and worst fit.
 *
 * @param policy_id representing the memory allocation policy
 * being adopted in this function call; 0 for first fit, 1
 * for best fit, and 2 for worst fit
 * @param size size of the memory chunk to be allocated
 * @return start of the memory chunk allocated
 */
void* allocate(int policy_id, size_t size);

/**
 * Finds the chunk of memory listed in allocated_list using the
 * inputted ptr and moves that chunk of memory to free_list.
 *
 * @param ptr pointer to allocated memory to be freed
 *
 * @return 0 if successful; otherwise, -1 if unsuccessful
 */
int deallocate(void* ptr);


/**
 * Prints the contents of the free list and allocated list.
 */
void print_mem_lists();

/**
 * Prints the average fragmentation within the memory allocated to
 * this memory allocator
 */
double average_frag();

/**
 * Generates a random number between the inputted starting and ending
 * integers.
 *
 * @param start integer which serves as the lower bound for random numbers produced
 * @param end integer which serves as the upper bound for random numbers produced
 * @return random number between start and end
 */
int random_number(int start, int end);

/**
 * Performs an inputted number of allocations and deallocations in
 * a 10K memory space and outputs the average fragmentation of memory
 * space; the allocations are made using a particular memory allocation
 * policy (see the parameter policy_id)
 *
 * @param policy_id represents the memory allocation policy that will be
 * used; 0 represents first fit, 1 represents best fit, and 2 represents
 * worst fit
 * @param seed seed to be used by the pseudo-random number generator
 * @param num_requests number of allocations and deallocations the memory
 * allocator will perform during the test
 * @return average fragmentation of memory allocation trial
 */
double frag_eval(int policy_id, unsigned int seed, int num_requests);

#endif /* _ALLOCATOR_H_ */
