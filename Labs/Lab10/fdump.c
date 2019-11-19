#include <stdio.h>
#include <stdlib.h>
#include "hexdump.h"

int main(int argc, char* argv[]) {
	if (argc != 4) {
		perror("Error: Usage ./fdump <filename> <offset> <size>\n");
		exit(-1);
	}
	
	FILE *fp = fopen(argv[1], "rw");
	if (fp == NULL) {
		perror("Error: Inputted filename could not be found.\n");
		perror("Error: Usage ./fdump <filename> <offset> <size>\n");
		exit(-1);
	}

	int ret_val = fseek(fp, atoi(argv[2]), SEEK_SET);
	if (ret_val == -1) {
		perror("Error: Could not advance file pointer by offset");
		perror("Error: Usage ./fdump <filename> <offset> <size>\n");
		exit(-1);

	}

	int num_bytes = atoi(argv[3])+1;
	char buffer[num_bytes];
	char* ret_p = fgets(buffer, num_bytes, fp);
	if (ret_p == NULL) {
		perror("Error: Could not read in bytes from file.\n");
		perror("Error: Usage ./fdump <filename> <offset> <size>\n");
		exit(-1);
	}
	
	hexdump((unsigned char*) buffer, num_bytes);

	fclose(fp);
	
	return 0;
}
