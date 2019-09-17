#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

pid_t Fork(void);
int Pipe(int pipefd[2]);
int Read(int fd, void *buf, size_t count);
int Write(int fd, const void *buf, size_t count);

pid_t Fork(void) {
    int pid = fork();
    if (pid == -1) {
        perror("Error occurred when creating the child process.");
        exit(-1);
    } else {
        return pid;
    }
}

int Pipe(int pipefd[2]) {
    int pipe_creation_status = pipe(pipefd);
    if (pipe_creation_status < 0) {
        perror("An error occurred while creating the pipe.");
        exit(-1);
    } else {
        return pipe_creation_status;
    }
}

int Read(int fd, void *buf, size_t count) {
    int num_bytes_read = read(fd, buf, count);
    if (num_bytes_read < 0) {
        perror("An error occurred while reading the file.");
        exit(-1);
    } else {
        return num_bytes_read;
    }
}

int Write(int fd, const void *buf, size_t count) {
    int num_bytes_written = write(fd, buf, count);
    if (num_bytes_written < 0) {
        perror("An error occurred while writing the file.");
        exit(-1); 
    } else {
        return num_bytes_written;
    }
}

int main(void) {
    char parent_buffer_write[BUFFER_SIZE] = "\0";
    char child_buffer_write[BUFFER_SIZE] = "\0";
    char child_buffer_read[BUFFER_SIZE] = "\0";
    char parent_buffer_write = "This      is     a     test      of    the    alert     system";

    int parent_to_child[2];
    int child_to_parent[2];
    int child_status;
    
    if (Pipe(parent_to_child) == -1) {
        fprintf(stderr, "Pipe parent to child failed");
        return 1;
    }
    if (Pipe(child_to_parent) == -1) {
        fprintf(stderr, "Pipe child to parent failed");
        return 1;
    }

    printf("Starting string: %s\n", parent_buffer_write);

    /* fork a child process */
    pid_t pid = Fork();

    if (pid < 0) { /* error occured */
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    if (pid > 0) { /* parent process */
        /* close the unused ends of the pipes */
        close(parent_to_child[READ_END]);
        close(child_to_parent[WRITE_END]);

        int str_length = strlen(parent_buffer_write);

        /* write 4 bytes to pipe and then remainder */
        Write(parent_to_child[WRITE_END], &str_len, 4);
        Write(parent_to_child[WRITE_END], parent_buffer_write, str_len+1);

        /* wait for child to finish processing */
        wait(&child_status);

        /* read from the pipe */
        str_length = 0;
        Read(child_to_parent[READ_END], &str_length, 4);
        Read(child_to_parent[READ_END], parent_buffer_read, BUFFER_SIZE);

        /* print output string */
        printf("Output string: %s\n", parent_buffer_read);

        /* close the unused ends of the pipes */
        close(parent_to_child[WRITE_END]);
        close(child_to_parent[READ_END]);

   } else { /* child process */
        /* close the used ends of the pipes */
        close(parent_to_child[WRITE_END]);
        close(child_to_parent[READ_END]);

        int str_length = 0;
        int is_data_coming_from_child;
        
        /* check for first four bytes */
        while ((is_data_coming_from_child = Read(parent_to_child[READ_END], &str_length, 4)) == 0);

        /* check for remainder of bytes */
       while ((is_data_coming_from_child = Read(parent_to_child[READ_END], child_buffer,_read, BUFFER_SIZE)) == 0);

        char word_read[];
        word = strtok(child_buffer_read, " ");

       while (word_read != NULL) {
           strcat(child_buffer_write, word_read);
           strcat(child_buffer_write, " ");
           word_read = strtok(NULL, " ");
       }


       child_buffer_write[strlen(child_buffer_write)-1] = '\0';

       str_length = strlen(child_buffer_write) + 1;
     
       
       Write(child_to_parent[WRITE_END], &str_length, 4);
       Write(child_to_parent[WRITE_END], child_buffer_write, str_length);

        /* close the used ends of the pipes */
        close(parent_to_child[READ_END]);
        close(child_to_parent[WRITE_END]);
   }
   return 0;
}
