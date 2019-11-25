#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef WRAPPERS_H
#define WRAPPERS_H

pid_t Fork(void);
int Pipe(int pipefd[2]);
pid_t Wait(int *status);
pid_t Waitpid(pid_t pid, int *status, int options);
int Open(const char *pathname, int flags);
int Close(int fd);
ssize_t Write(int fd, const void *buf, size_t count);
ssize_t Read(int fd, void *buf, size_t count);
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int Execvp(const char* path, char* const argv[]);

#endif  
