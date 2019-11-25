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
 * This enum type represents a memory allocation
 * algorithm to be used by the allocate function
 * 	- first-fit represented by FIRST_FIT
 * 	- best-fit represented by BEST_FIT
 * 	- worst-fit represented by WORST_FIT
 */
enum ALLOC_ALGO {FIRST_FIT, BEST_FIT, WORST_FIT};
extern enum ALLOC_ALGO alloc_algo;

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
 * Finds a chunk of memory of at least the inputted size that can
 * be allocated using the first-fit, best-fit, or worst-fit memory
 * allocation algorithms. The allocated chunk is removed from a portion
 * of a node in free_list and moved to allocated_list.
 *
 * @param size size of memory chunk to be allocated
 *
 * @return pointer to the chunk of memory allocated
 */
void* allocate(size_t size);

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

#endif /* _ALLOCATOR_H_ */
