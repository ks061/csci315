#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("Usage: ./cmdreverse <string>\n");
	} else if (argc != 2) {
		printf("Error: Please enter exactly one argument.\n");
		printf("Usage: ./cmdreverse <string>\n");
	} else {
		char* input = argv[1];
		char* output = malloc(sizeof(input));

		int output_index = 0;
		int input_index;
		for (input_index = strlen(input) - 1; input_index >= 0; input_index--) {
			output[output_index] = input[input_index];
			output_index++;
		}
		printf("%s\n", output);
		free(output);
	}
	
	exit(0);
}
