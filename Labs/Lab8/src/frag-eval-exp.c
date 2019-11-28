#include <stdlib.h>
#include <stdio.h>

#include "dnode.h"
#include "dlist.h"
#include "allocator.h"

#define NUM_SAMPLES 1000
#define NUM_REQUESTS 100

int main() {
	// average fragmentation for each sample across 
	// each memory allocation policy tested on
	double first_fit_avg_frag[NUM_SAMPLES];
	double best_fit_avg_frag[NUM_SAMPLES];
	double worst_fit_avg_frag[NUM_SAMPLES];

	int policy_id;
	int i;

	policy_id = 0; // first fit
	for (i = 0; i < NUM_SAMPLES; i++) {
		first_fit_avg_frag[i] = frag_eval(policy_id, i, NUM_REQUESTS);
	}

	policy_id = 1; // best fit
	for (i = 0; i < NUM_SAMPLES; i++) {
		best_fit_avg_frag[i] = frag_eval(policy_id, i, NUM_REQUESTS);
	}
	
	policy_id = 2; // worst fit
	for (i = 0; i < NUM_SAMPLES; i++) {
		worst_fit_avg_frag[i] = frag_eval(policy_id, i, NUM_REQUESTS);
	}

	FILE *fp = fopen("avg_frag_exp_data.txt", "w");
	if (fp == NULL) {
		printf("Error: Could not write to file!\n");
		exit(1);
	}

	for (i = 0; i < NUM_SAMPLES; i++) {
		fprintf(fp, "%lf %lf %lf\n", first_fit_avg_frag[i], best_fit_avg_frag[i], worst_fit_avg_frag[i]);
	}

	fclose(fp);
	return 0;
}
