/**
 * Additional Feature: shell exits upon typing 'exit\n' into the command line window.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "wrappers.h"

#define MAX_INPUT_SIZE 1024
#define MAX_NUM_ARGS 10

static void print_term_code(int status) {
	int term_code = WEXITSTATUS(status);
	if (term_code > 0) printf("[ishell: program terminated abnormally][\"%d\"]\n", term_code);
	else printf("[ishell: program terminated successfully]\n");
}

int main(int argc, char *argv[]) {
	char input_str[MAX_INPUT_SIZE];

	char *cmd_token, *arg_token;
	char *cmd_saveptr, *arg_saveptr;
	char **cmd_args;
	
	int i;

	int pid;
	int status;
	while (1) {
		printf("ishell> ");

		if (!fgets(input_str, MAX_INPUT_SIZE, stdin)) 
			break; // break if no more input
		if (strcmp(input_str, "exit\n") == 0)
			break; // break if exit command entered
		
		if (strlen(input_str) == 1)		
			if (input_str[0] == '\n')
				fgets(input_str, MAX_INPUT_SIZE, stdin);
					if (input_str[0] == '\n') {
						pid = Fork();
						if (pid == 0) {
							cmd_args = malloc(sizeof(char*));
							cmd_args[0] = "ls";
							Execvp(cmd_args[0], cmd_args);
						} else {
							Wait(&status);
							print_term_code(status);
						}
						continue;		
					}	
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
			if (pid == 0)
				Execvp(cmd_args[0], cmd_args);
			else {
				Wait(&status);
				print_term_code(status);
			}
			free(cmd_args[i]);
			cmd_token = strtok_r(NULL, ";", &cmd_saveptr);
		}
		
	}
	return 0;
}
