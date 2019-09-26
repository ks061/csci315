#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("Usage: ./cmds <char> <int> <float> <string>\n");
	} else if (argc != 5) {
		printf("Error: Please enter exactly four arguments.\n");
		printf("Usage: ./cmds <char> <int> <float> <string>\n");
	} 
	else {
		char parameter_one = argv[1][0];
		int parameter_two = atoi(argv[2]);
		float parameter_three = atof(argv[3]);
		char* parameter_four = argv[4];

		printf("%c\n", parameter_one);
		printf("%d\n", parameter_two);
		printf("%f\n", parameter_three);
		printf("%s\n", parameter_four);
	}
	
	exit(0);
}
