#include "shell.h"

/**
 * execute_command - function to execute command
 * @command : arg
 * Return: nathing
 */

void execute_command(char *command)
{
	char *args[MAX_COMMAND_LENGTH];
	int i = 0;
	char *token = strtok(command, " ");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	execvp(args[0], args);

	perror("");
	exit(EXIT_FAILURE);
}

/**
 * exit - Function to handle the built-in exit command
 * @status : arg
 * Rutern: nothing
 */
void comm_exit(char *status)
{
	int exit_status = atoi(status);

	exit(exit_status);
}

/**
 * env - Function to handle the built-in env command
 * @void : arg
 * Rutern: nothing
 */
void env(void)
{
	extern char **environ;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/**
 * cd - Function to handle the built-in cd command
 * @dir : arg
 * Rutern: nothing
 */
void cd(char *dir)
{
	if (chdir(dir) != 0)
	{
		perror("");
	}
}
