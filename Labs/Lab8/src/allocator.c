#include "allocator.h"
#include "dlist.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct dlist* free_list;
struct dlist* allocated_list;
void* contig_space;
size_t total_size;
int num_fragments;

/**
 * Initializes a memory allocator with a particular amount of
 * bytes of memory.
 *
 * @param size size in bytes of memory to be handled by this memory allocator
 */
int allocator_init(size_t size) {
    if (free_list != NULL) free(free_list);
    if (allocated_list != NULL) free(allocated_list);
    if (contig_space != NULL) free(contig_space);
    free_list = dlist_create();
    allocated_list = dlist_create(); 
    contig_space = malloc(size);
    total_size = size;
    num_fragments = 0;
    
    if (contig_space == NULL) { return -1; }
    else {
	dlist_add_front(free_list, contig_space, size);
        return 0;
    }
}

/**
 * Adjusts the pointer and size of the free node being allocated from
 * and adds a chunk of memory to allocated_list. The node is removed from
 * the free list all together if all of that node has been allocated.
 *
 * @param size amount of space being allocated
 * @param iter_node free node being allocated from
 * 
 * @return pointer to start of allocated chunk of memory
 */
static void* allocate_ptr_adjust(size_t size, struct dnode* iter_node) { 
    void* alloc_contig_space = iter_node->ptr;
    iter_node->ptr += size;
    iter_node->size -= size;
    if (iter_node->size == 0) {
	dlist_find_remove(free_list, iter_node->ptr);
    }
    dlist_add_in_place(allocated_list, alloc_contig_space, size);
    return alloc_contig_space;
}

/**
 * Allocate a chunk of memory of the inputted size
 * using the first fit memory allocation policy
 *
 * @param size size of the memory to be allocated
 * @return start of the memory chunk to be allocated
 */
static void* allocate_first_fit(size_t size) {
    struct dnode* iter_node = dlist_iter_begin(free_list);
    do {
	if (size <= iter_node->size) {
        	return allocate_ptr_adjust(size, iter_node);
	}     
    } while ((iter_node = dlist_iter_next(free_list)) != NULL);
    return NULL;
}

/**
 * Find either the best or worst fitting free node that
 * has enough space to meet the allocation requirement of the
 * inputted sizen
 *
 * @param policy_id representing the memory allocation policy
 * being adopted in this function call; 0 for first fit, 1
 * for best fit, and 2 for worst fit
 * @param size size of the memory chunk to be allocated
 * @return pointer to the start of the allocated memory chunk
 */
static void* allocate_extreme_fit(int policy_id, size_t size) {
    struct dnode* extreme_fit_node = NULL;
    struct dnode* iter_node = dlist_iter_begin(free_list);
    do {
	if (size <= iter_node->size) {
		if (extreme_fit_node == NULL) { 
			extreme_fit_node = iter_node; 
		}
            	else if (policy_id == 1 && iter_node->size < extreme_fit_node->size) { 
			extreme_fit_node = iter_node; 
		} 
		else if (policy_id == 2 && iter_node->size > extreme_fit_node->size) {
			extreme_fit_node = iter_node;
		}
	}
    } while ((iter_node = dlist_iter_next(free_list)) != NULL);
    
    if (extreme_fit_node != NULL) {
    	return allocate_ptr_adjust(size, extreme_fit_node);
    }
    return NULL;
}

/**
 * Allocates a chunk of memory based on the best
 * fit memory allocation policy
 *
 * @param size size of the memory chunk to be allocated
 * @return pointer to the start of the memory chunk allocated
 */
static void* allocate_best_fit(size_t size) {
    return allocate_extreme_fit(1, size);
}

/**
 * Allocates a chunk of memory based on the worst
 * fit memory allocation policy
 *
 * @param size size of the memory chunk to be allocated
 * @return pointer to the start of the memory chunk allocated
 */
static void* allocate_worst_fit(size_t size) {
    return allocate_extreme_fit(2, size);
}

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
void* allocate(int policy_id, size_t size) {
    if (free_list == NULL) perror("Error: Call allocate_init before allocate.");
    if (allocated_list == NULL) perror("Error: Call allocate_init before allocate.");
    if (contig_space == NULL) perror("Error: Call allocate_init before allocate.");
    if (size == 0) return NULL;
    if (dlist_iter_begin(free_list) == NULL) return NULL;
    void* allocated_memory = NULL; 
    switch (policy_id) {
	case 0: 
		allocated_memory = allocate_first_fit(size);
		if (allocated_memory != NULL) num_fragments += 1;
		return allocated_memory;
		break;
	case 1: 
		allocated_memory = allocate_best_fit(size);
		if (allocated_memory != NULL) num_fragments += 1;
		return allocated_memory;
		break;
	case 2: 
		allocated_memory = allocate_worst_fit(size);
		if (allocated_memory != NULL) num_fragments += 1;
		return allocated_memory;
		break;
	default: perror("Error: Allocation algorithm must be either FIRST_FIT, BEST_FIT, or WORST_FIT, \
which represent the first_fit, best_fit, and worst_fit memory allocation \
algorithms respectively. Please check the alloc_algo variable in allocator.h.");
    		 return NULL;
    }
}

/**
 * Deallocates a chunk of memory
 *
 * @param ptr start of the chunk of memory to be deallocated
 * @return 0 if successful; -1 if unsuccessful, namely either the pointer is
 * null or the node to be removed could not be found in the allocated list
 */
int deallocate(void* ptr) {
    if (ptr == NULL) { return -1; }
    struct dnode* node_to_deallocate = dlist_find_remove(allocated_list, ptr);
    if (node_to_deallocate == NULL) { return -1; }
    else {	
      dlist_add_in_place(free_list, node_to_deallocate->ptr, node_to_deallocate->size);
    }
    return 0;
}

/**
 * Prints each node in the free list, i.e. its starting and ending
 * indices relative to the starting bit of the memory allocator.
 */
static void print_free_list() {
        printf("  Iterating through free list of memory chunks:\n");
        struct dnode* cur_node = dlist_iter_begin(free_list);
        while (cur_node != NULL) {
                printf("    Free: %d - %d\n", (int)((cur_node->ptr)-contig_space), (int)((cur_node->ptr)-contig_space+(cur_node->size)-1));
                cur_node = dlist_iter_next(free_list);
        }
}

/**
 * Prints each node in the allocated list, i.e. its starting and ending
 * indices relative to the starting bit of the memory allocator.
 */
static void print_allocated_list() {
	printf("  Iterating through allocated list of memory chunks:\n");
        struct dnode* cur_node = dlist_iter_begin(allocated_list);
        while (cur_node != NULL) {
                printf("    Allocated: %d - %d\n", (int)((cur_node->ptr)-contig_space), (int)((cur_node->ptr)-contig_space+(cur_node->size)-1));
                cur_node = dlist_iter_next(allocated_list);
        }
}

/**
 * Prints the free and allocated memory lists; for each node, the starting
 * and ending indices relative to the starting bit of the memory allocator,
 * are printed.
 */
void print_mem_lists() {
	print_free_list();
	print_allocated_list();
	printf("\n");
}

/**
 * Gets the average fragmentation within the memory chunk that the
 * memory allocator handles.
 *
 * @return average fragmentation within the memory chunk that the memory
 * allocator handles
 */
double average_frag() {
	return (double) total_size / (double) num_fragments;
}

/**
 * Generates a random number between the inputted starting and ending
 * integers.
 *
 * @param start integer which serves as the lower bound for random numbers produced
 * @param end integer which serves as the upper bound for random numbers produced
 * @return random number between start and end
 */
int random_number(int start, int end) {
	int range = end - start;
	double fraction = (double) rand() / RAND_MAX;
	
	// 0.5 added to fraction to account for rounding up since
	// (int) simply truncates the number
	int random_num = start + (int) (fraction * range + 0.5);

	return random_num;
}

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
double frag_eval(int policy_id, unsigned int seed, int num_requests) {
	// initializing allocator with 10K of memory
	allocator_init(10240);

	// initializing the pseudo-random number generator
	srand(seed);

	// number of requests processed
	int r = 0;
	// array of pointers to allocations
	void **p[num_requests];
	// generated pseudo-random number
	int s = 0;

	while (r < num_requests) {
		s = random_number(100, 1000);
		p[r] = allocate(policy_id, s);
		r++;
	}
	
	r = 0;
	while (r < num_requests) {
		if (p[r] != NULL) deallocate(p[r]);
		r++;
	}

	return average_frag();
}

