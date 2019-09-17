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
    char msg[] = "Greetings";
    char child_char_read, child_char_written;
    char parent_char_read, parent_char_written;

    int parent_to_child[2];
    int child_to_parent[2];
    
    if (Pipe(parent_to_child) == -1) {
        fprintf(stderr, "Pipe parent to child failed");
        return 1;
    }
    if (Pipe(child_to_parent) == -1) {
        fprintf(stderr, "Pipe child to parent failed");
        return 1;
    }

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

        /* read from the pipe */
        int write_index = 0;
        parent_char_written = msg[0];
        while(parent_char_written != 0) {
            Write(parent_to_child[WRITE_END], &parent_char_written, 1); 
            write_index++;
            parent_char_written = msg[write_index];
        }

        close(parent_to_child[WRITE_END]);
        
        while(Read(child_to_parent[READ_END], &parent_char_read, 1) > 0) {
            printf("Character read by parent process: %c\n", parent_char_read);
        }

        /* close the unused ends of the pipes */
        close(child_to_parent[READ_END]);

   } else { /* child process */
        /* close the used ends of the pipes */
        close(parent_to_child[WRITE_END]);
        close(child_to_parent[READ_END]);

        /* write to the pipe one character at a time */
        while (Read(parent_to_child[READ_END], &child_char_read, 1) > 0) {
            printf("Character read by child process: %c\n", child_char_read);
            child_char_written = toupper(child_char_read); 
            Write(child_to_parent[WRITE_END], &child_char_written, 1);
        }

        /* close the used ends of the pipes */
        close(parent_to_child[READ_END]);
        close(child_to_parent[WRITE_END]);
   }
   return 0;
}
