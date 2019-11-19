#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "wrappers.h"

#define MAX_INPUT_SIZE 1024
#define MAX_NUM_ARGS 10

int main(int argc, char *argv[]) {
	char input_str[MAX_INPUT_SIZE];
	
	char* token;
	char** cmd_args = malloc(sizeof(char*) * MAX_NUM_ARGS);
	int i;

	int pid;
	int status;
	while (1) {
		printf("ishell> ");

		if (!fgets(input_str, MAX_INPUT_SIZE, stdin)) 
			break; // break if no more input
		if (strcmp(input_str, "exit\n") == 0)
			break; // break if exit command entered
		if (input_str[strlen(input_str)-1] == '\n')
			input_str[strlen(input_str)-1] = '\0';

		token = strtok(input_str, " ");
		i = 0;
		while (token) {
			cmd_args[i++] = token;
			token = strtok(NULL, " ");
		}
		cmd_args[i] = NULL;

		pid = Fork();
		if (pid == 0) {
			Execvp(cmd_args[0], cmd_args);		
		} else {
			Wait(&status);
		}
	}
	return 0;
}
