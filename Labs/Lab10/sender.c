#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>

#define MAX_BUF_LEN 256

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: ./sender [message]\n");
		return -1;
	}

        sem_t* semaphore = sem_open("ks061", O_CREAT, 0700, 1);

	// Named semaphore enables writing to file is available
	// to only one sender at a time
	sem_wait(semaphore);
	// File pointers allowed me to effectively keep track of the next
	// place to write.
	FILE* fp = fopen("channel.txt", "a");
	fputs(argv[1], fp);
	fputs("\n", fp);
	fclose(fp);	
	sem_post(semaphore);


	return 0;
}
