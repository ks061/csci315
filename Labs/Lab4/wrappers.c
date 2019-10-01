#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


pid_t Fork(void) {
    // fork a child and get a pid
    pid_t pid = fork();

    if (pid >= 0) return pid; // return PID on successful fork 
    else { // error out if fork unsuccessful
        perror("Error: Forking has failed.\n");
        exit(-1);
    }
}

int Pipe(int pipefd[2]) {
    // create a pipe
    int pipe_creation_status = pipe(pipefd);

    if (pipe_creation_status == 0) return 0; // pipe successfully created
    else { // error out if pipe creation unsuccessful
        perror("Error: Pipe creation has failed.\n");
        exit(-1);
    }
}

pid_t Wait(int *status) {
    // wait for a child process
    pid_t child_process_pid = wait(status);    

    if (child_process_pid > 0) return child_process_pid; // successful termination of
                                                         // child process waited for
    else { // error out if child could not be waited on
        perror("Error: Child could not be waited on/PID of child process not received.\n");
        exit(-1);
    }
}

pid_t Waitpid(pid_t pid, int *status, int options) {
    // wait for a child process with the given pid
    pid_t child_process_pid = waitpid(pid, status, options);    

    if (child_process_pid > 0) return child_process_pid; // successful termination of
                                                         // child process waited for
    else { // error out if child could not be waited on
        perror("Error: Child with specific PID could not be waited on/PID of child process not received.\n");
        exit(-1);
    }
}

int Open(const char *pathname, int flags) {
    // opening a file
    int fd = open(pathname, flags);
  
    if (fd == -1) { // return an error if opening of a file failed
        perror("Error: Opening a file failed.\n");
        exit(-1); 
    }

    return fd; // otherwise, return a file descriptor of the file successfully opened
}

int Close(int fd) {
    // closing a file
    int close_status = close(fd);
  
    if (close_status == 0) return 0; // successful closure of file
    else { // error out if could not close file
        perror("Error: Closing a file failed.\n");
        exit(-1);
    }
}

ssize_t Write(int fd, const void *buf, size_t count) {
    // writing to a file
    ssize_t num_bytes_written = write(fd, buf, count);

    if (num_bytes_written >= 0) return num_bytes_written; // returns number of bytes written if operation
                                                          // successful (0 returned if no bytes written)
    else { // error out if could not write to file
        perror("Error: Write to file failed.\n");
        exit(-1);
    } 
}

ssize_t Read(int fd, void *buf, size_t count) {
    // reading from a file
    ssize_t num_bytes_read = read(fd, buf, count);

    if (num_bytes_read >= 0) return num_bytes_read; // returns number of bytes read if operation
                                                    // successful (0 returned if no bytes read)
    else { // error out if could not read from file
        perror("Error: Reading to file failed.\n");
        exit(-1);
    }
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    // establish a connection on a socket
    int connect_status = connect(sockfd, addr, addrlen);
    
    if (connect_status == 0) return 0; // return 0 for successful connection
    else { // error out if could not connect on a socket
        perror("Error: Connection on socket failed.\n");
        exit(-1);
    }
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    // bind a name to a socket
    int bind_status = bind(sockfd, addr, addrlen);

    if (bind_status == 0) return 0; // return 0 for successful binding
    else { // error out if could not bind name to socket
        perror("Error: Could not bind name to socket.\n");
        exit(-1);
    }
}

int Listen(int sockfd, int backlog) {
    // listen for connections on socket
    int listen_status = listen(sockfd, backlog);
    
    if (listen_status == 0) return 0; // return 0 for successful listening
    else { // error out if could not listen for connections on socket
        perror("Error: Could not listen to connections on socket.\n");
        exit(-1);
    } 
}


int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    // accept connection on socket
    int accepted_sock_descriptor = accept(sockfd, addr, addrlen);

    // return descriptor of sock on which connection was accepted
    if (accepted_sock_descriptor >= 0) return accepted_sock_descriptor;
    else { // error out if could not accept connection on socket
        perror("Error: Could not accept connection on socket.\n");
        exit(-1);
    }
}
