#include "allocator.h"
#include "dlist.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct dlist* free_list;
struct dlist* allocated_list;
void* contig_space;
size_t contig_space_size;

enum ALLOC_ALGO alloc_algo;

int allocator_init(size_t size) {
    if (free_list != NULL) free(free_list);
    if (allocated_list != NULL) free(allocated_list);
    if (contig_space != NULL) free(contig_space);
    free_list = dlist_create();
    allocated_list = dlist_create(); 
    contig_space = malloc(size);

    if (contig_space == NULL) { return -1; }
    else {
	dlist_add_front(free_list, contig_space, size);
        return 0;
    }
}

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

static void* allocate_first_fit(size_t size) {
    struct dnode* iter_node = dlist_iter_begin(free_list);
    do {
	if (size <= iter_node->size) {
        	return allocate_ptr_adjust(size, iter_node);
	}     
    } while ((iter_node = dlist_iter_next(free_list)) != NULL);
    return NULL;
}

static void* allocate_extreme_fit(size_t size) {
    struct dnode* extreme_fit_node = NULL;
    struct dnode* iter_node = dlist_iter_begin(free_list);
    do {
	if (size <= iter_node->size) {
		if (extreme_fit_node == NULL) { 
			extreme_fit_node = iter_node; 
		}
            	else if (alloc_algo == BEST_FIT && iter_node->size < extreme_fit_node->size) { 
			extreme_fit_node = iter_node; 
		} 
		else if (alloc_algo == WORST_FIT && iter_node->size > extreme_fit_node->size) {
			extreme_fit_node = iter_node;
		}
	}
    } while ((iter_node = dlist_iter_next(free_list)) != NULL);
    
    if (extreme_fit_node != NULL) {
    	return allocate_ptr_adjust(size, extreme_fit_node);
    }
    return NULL;
}

static void* allocate_best_fit(size_t size) {
    return allocate_extreme_fit(size);
}

static void* allocate_worst_fit(size_t size) {
    return allocate_extreme_fit(size);
}

void* allocate(size_t size) {
    if (free_list == NULL) perror("Error: Call allocate_init before allocate.");
    if (allocated_list == NULL) perror("Error: Call allocate_init before allocate.");
    if (contig_space == NULL) perror("Error: Call allocate_init before allocate.");
    if (size == 0) return NULL;
    if (dlist_iter_begin(free_list) == NULL) return NULL; 
    switch (alloc_algo) {
	case FIRST_FIT: return allocate_first_fit(size);
		break;
	case BEST_FIT: return allocate_best_fit(size);
		break;
	case WORST_FIT: return allocate_worst_fit(size);
		break;
	default: perror("Error: Allocation algorithm must be either FIRST_FIT, BEST_FIT, or WORST_FIT, \
which represent the first_fit, best_fit, and worst_fit memory allocation \
algorithms respectively. Please check the alloc_algo variable in allocator.h.");
    		 return NULL;
    }
}

int deallocate(void* ptr) {
    if (ptr == NULL) { return -1; }
    struct dnode* node_to_deallocate = dlist_find_remove(allocated_list, ptr);
    if (node_to_deallocate == NULL) { return -1; }
    else {	
      dlist_add_in_place(free_list, node_to_deallocate->ptr, node_to_deallocate->size);
    }
    return 0;
}

static void print_free_list() {
        printf("  Iterating through free list of memory chunks:\n");
        struct dnode* cur_node = dlist_iter_begin(free_list);
        while (cur_node != NULL) {
                printf("    Free: %d - %d\n", (int)((cur_node->ptr)-contig_space), (int)((cur_node->ptr)-contig_space+(cur_node->size)-1));
                cur_node = dlist_iter_next(free_list);
        }
}

static void print_allocated_list() {
	printf("  Iterating through allocated list of memory chunks:\n");
        struct dnode* cur_node = dlist_iter_begin(allocated_list);
        while (cur_node != NULL) {
                printf("    Allocated: %d - %d\n", (int)((cur_node->ptr)-contig_space), (int)((cur_node->ptr)-contig_space+(cur_node->size)-1));
                cur_node = dlist_iter_next(allocated_list);
        }
}

void print_mem_lists() {
	print_free_list();
	print_allocated_list();
	printf("\n");
}
