#include "shell.h"

/**
 * main - fnuction main
 * @argc : arg
 * @argv : arg
 * Return: 0
 */
int main(int argc, char *argv[])
{
	char command[MAX_COMMAND_LENGTH];
	int interactive = isatty(fileno(stdin));

	while (1)
	{
		if (interactive)
			printf("$ ");

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			if (interactive)
			{
				printf("\n");
			}
			break;
		}
		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0)
			comm_exit("0");
		else if (strcmp(command, "env") == 0)
			env();
		else if (strncmp(command, "cd ", 3) == 0)
			cd(command + 3);
		else
		{
			pid_t pid = fork();

			if (pid == -1)
			{
				perror("");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
				execute_command(command);
			else
				wait(NULL);
		}
	}
	return (0);
}
