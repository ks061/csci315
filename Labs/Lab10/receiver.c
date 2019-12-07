#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	// Semaphore is created in receiver because only one instance of it exists
	sem_open("ks061", O_CREAT, 00700, 1);
	char char_received = '\0';

	// File pointers allowed me to effectively keep track of the next
	// place to write.
	FILE* fp = fopen("channel.txt", "w");
	fp = freopen("channel.txt", "r", fp);	
	
	while (1) {
		char_received = fgetc(fp);
		printf("> receiver [msg arrival]: \"");
		while (char_received != '\n') {
			if (char_received != EOF)
				printf("%c", char_received);
			char_received = fgetc(fp);
		}
		printf("\"\n"); 
	}
	return 0;
}
