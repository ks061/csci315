#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"
#include "dlist.h"

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Format: frag-eval [algorithm] [seed] [requests]\n");
		return -1;
	}
	
	int policy_id = atoi(argv[1]);
	unsigned int seed = *((unsigned int *)argv[2]);
	int num_requests = atoi(argv[3]);
	
	return average_frag(policy_id, seed, num_requests);
}
