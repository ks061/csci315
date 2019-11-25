#include <stdio.h>
#include "allocator.h"
#include "dlist.h"

extern struct dlist* free_list;
extern struct dlist* allocated_list;
extern enum ALLOC_ALGO alloc_algo;

void* start;

int main(int argc, char* argv[]) {
	/* Testing initialization of memory allocator */
	int ret_val;
	size_t size = 144;
        ret_val = allocator_init(size);	
	if (ret_val == 0) {
		printf("*************************************************\n");
		printf("*Initialized allocator with %zu bytes of memory.*\n", size);
		printf("*************************************************\n");
		print_mem_lists();
	}

	// Testing first fit memory allocation
	alloc_algo = FIRST_FIT;
        void* allocated_mem_1 = NULL;
	void* allocated_mem_2 = NULL;
	void* allocated_mem_3 = NULL;
	void* allocated_mem_4 = NULL;
	printf("************************************************\n");
	printf("*Testing first fit memory allocation algorithm.*\n");
	printf("************************************************\n");
	printf("Allocating 30 bytes\n");
	allocated_mem_1 = allocate(30);
	print_mem_lists();	
	printf("Allocating 30 bytes\n");
	allocated_mem_2 = allocate(30);
	print_mem_lists();
	printf("Allocating 84 bytes\n");
	allocated_mem_3 = allocate(84);
	print_mem_lists();
	printf("Allocating 30 bytes\n");
	allocated_mem_4 = allocate(30);	
	if (allocated_mem_4 == NULL)
		printf("Correctly returned NULL pointer due to their not \
being any more free space for allocation.\n");
	print_mem_lists();

	// Testing deallocation of memory allocation
	printf("***********************\n");
	printf("*Testing deallocation.*\n");
	printf("***********************\n");
	printf("Deallocating middle 30 bytes.\n");
	deallocate(allocated_mem_2);
	print_mem_lists();
	printf("Deallocating last 84 bytes.\n");
	deallocate(allocated_mem_3);
	print_mem_lists();
	printf("Deallocating first 30 bytes.\n");
	deallocate(allocated_mem_1);
	print_mem_lists();

	// Resetting memory allocator and related pointers
	allocator_init(size);
	if (ret_val == 0) {
		printf("*************************************************\n");
		printf("*Initialized allocator with %zu bytes of memory.*\n", size);
		printf("*************************************************\n");
		print_mem_lists();
	}
	allocated_mem_1 = NULL;
	allocated_mem_2 = NULL;
	allocated_mem_3 = NULL;
	allocated_mem_4 = NULL;

	// Testing best fit memory allocation
	alloc_algo = BEST_FIT;
	printf("***********************************************\n");
	printf("*Testing best fit memory allocation algorithm.*\n");
	printf("***********************************************\n");
	printf("Allocating 30 bytes.\n");
	allocated_mem_1 = allocate(30);
	print_mem_lists();
	printf("Allocating 1 byte.\n");
	allocated_mem_3 = allocate(1);
	print_mem_lists();
	printf("Deallocating 30 bytes.\n");
	deallocate(allocated_mem_1);
	print_mem_lists();
	printf("Allocating 29 bytes.\n");
	allocated_mem_1 = allocate(29);
	print_mem_lists();
	printf("Allocating 1 byte.\n");
	allocated_mem_2 = allocate(1);
	print_mem_lists();


	// Resetting memory allocator and related pointers
	allocator_init(size);
	if (ret_val == 0) {
		printf("*************************************************\n");
		printf("*Initialized allocator with %zu bytes of memory.*\n", size);
		printf("*************************************************\n");
		print_mem_lists();
	}
	allocated_mem_1 = NULL;
	allocated_mem_2 = NULL;
	allocated_mem_3 = NULL;
	allocated_mem_4 = NULL;

	// Testing worst fit memory allocation
	alloc_algo = WORST_FIT;
	printf("************************************************\n");
	printf("*Testing worst fit memory allocation algorithm.*\n");
	printf("************************************************\n");
	printf("Allocating 30 bytes.\n");
	allocated_mem_1 = allocate(30);
	print_mem_lists();
	printf("Allocating 1 byte.\n");
	allocated_mem_3 = allocate(1);
	print_mem_lists();
	printf("Deallocating 30 bytes.\n");
	deallocate(allocated_mem_1);
	print_mem_lists();
	printf("Allocating 29 bytes.\n");
	allocated_mem_1 = allocate(29);
	print_mem_lists();
	printf("Allocating 1 byte.\n");
	allocated_mem_2 = allocate(1);
	print_mem_lists();
}
