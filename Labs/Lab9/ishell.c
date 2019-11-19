#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "wrappers.h"

#define MAX_INPUT_SIZE 1024
#define MAX_NUM_ARGS 10

int main(int argc, char *argv[]) {
	char input_str[MAX_INPUT_SIZE];

	char *cmd_token, *arg_token;
	char *cmd_saveptr, *arg_saveptr;
	char **cmd_args;
	
	int i;

	int pid;
	int status;
	int termination_status;
	while (1) {
		printf("ishell> ");

		if (!fgets(input_str, MAX_INPUT_SIZE, stdin)) 
			break; // break if no more input
		if (strcmp(input_str, "exit\n") == 0)
			break; // break if exit command entered
		if (input_str[strlen(input_str)-1] == '\n')
			input_str[strlen(input_str)-1] = '\0'; // replace new line character
							       // used in command line UI with
							       // null terminator used to handle
							       // strings in C
		
		cmd_token = strtok_r(input_str, ";", &cmd_saveptr);
		while (cmd_token) {
			arg_token = strtok_r(cmd_token, " ", &arg_saveptr);
			i = 0;
			cmd_args = malloc(sizeof(char*) * MAX_NUM_ARGS);
			while (arg_token) {
				cmd_args[i++] = arg_token;
				arg_token = strtok_r(NULL, " ", &arg_saveptr);
			}
			cmd_args[i] = NULL;
			pid = Fork();
			if (pid == 0) {
				Execvp(cmd_args[0], cmd_args);
			} else {
				Wait(&status);
				termination_status = WEXITSTATUS(status);
				if (termination_status > 0) printf("[ishell: program terminated abnormally][\"%d\"]\n", termination_status);
				else printf("[ishell: program terminated successfully]\n");
			}
			free(cmd_args[i]);
			cmd_token = strtok_r(NULL, ";", &cmd_saveptr);
		}
		
	}
	return 0;
}
