#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10


char *read_command(int is_interactive)
{
	if (is_interactive)
	{
		write(STDOUT_FILENO, "$ ", 3);
	}

	char *command = malloc(MAX_COMMAND_LENGTH * sizeof(char));

	if (command == NULL)
	{
		perror("");
		exit(EXIT_FAILURE);
	}

	ssize_t read_size = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);

	if (read_size == -1)
	{
		perror("");
		free(command);
		return (NULL);
	}
	else if (read_size == 0)
	{
		free(command);
		return (NULL);
	}

	if (command[read_size - 1] == '\n')
	{
		command[read_size - 1] = '\0';
	}

	return (command);
}

void execute_command(char **args)
{
	if (args[0] == NULL)
	{
		return;
	}

	char *exit_cmd = "exit";
	char *env_cmd = "env";
	char *cd_cmd = "cd";

	if (str_equal(args[0], exit_cmd)
		|| str_equal(args[0], env_cmd)
		|| str_equal(args[0], cd_cmd))
	{
		execute_int_command(args);
	}
	else
	{
		pid_t pid = fork();
		int status;

		if (pid == -1)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(args[0], args, NULL);
			perror("");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
}

void free_args(char **args)
{
	if (args == NULL)
	{
		return;
	}

	for (int i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}
