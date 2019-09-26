#include <stdio.h>
#include <unistd.h>

int main(void) {
	int count = 1;
	int child_one = fork();
	int child_two = fork();
	if (child_one > 0 && child_two > 0) {
		while (1) {
			printf("Parent: %d\n", count);
			count++;
		}
	} else if (child_one == 0 && child_two > 0) {
		while (1) {
			printf("Child #1: %d\n", count);
			count++;
		}
	} else if (child_one > 0 && child_two == 0) {
		while (1) {
			printf("Child #2: %d\n", count);
			count++;
		}
	} else {
	}
	return 0;
}
