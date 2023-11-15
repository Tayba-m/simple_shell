#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

/**
 * main - the main function
 * @void : arg
 * Return: 0
 */

int main(void)
{
	int is_interactive = isatty(STDIN_FILENO);

	if (!is_interactive)
	{
		char *command = read_command(is_interactive);

		if (command == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			return (0);
		}

		char *token;
		char **args = malloc(MAX_ARGS * sizeof(char *));

		if (args == NULL)
		{
			perror("");
			exit(EXIT_FAILURE);
		}

		int i = 0;

		token = strtok(command, " ");

		while (token != NULL && i < MAX_ARGS - 1)
		{
			args[i] = malloc(MAX_COMMAND_LENGTH * sizeof(char));

			if (args[i] == NULL)
			{
				perror("");
				exit(EXIT_FAILURE);
			}
			strncpy(args[i], token, MAX_COMMAND_LENGTH - 1);
			args[i][MAX_COMMAND_LENGTH - 1] = '\0';
			i++;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		execute_command(args);
		free(command);
		free_args(args);
		return (0);
	}

	while (1)
	{
		char *command = read_command(is_interactive);

		if (command == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		char *token;
		char **args = malloc(MAX_ARGS * sizeof(char *));

		if (args == NULL)
		{
			perror("");
			exit(EXIT_FAILURE);
		}

		int i = 0;

		token = strtok(command, " ");

		while (token != NULL && i < MAX_ARGS - 1)
		{
			args[i] = malloc(MAX_COMMAND_LENGTH * sizeof(char));

			if (args[i] == NULL)
			{
				perror("");
				exit(EXIT_FAILURE);
			}
			strncpy(args[i], token, MAX_COMMAND_LENGTH - 1);
			args[i][MAX_COMMAND_LENGTH - 1] = '\0';
			i++;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		execute_command(args);
		free(command);
		free_args(args);
	}

	return (0);
}
