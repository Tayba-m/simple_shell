#include "shell.h"

/**
 * exec_com - function to execute command
 * @args: arguments list
 * Return: exit status, -1 otherwise
 */

int exec_com(char *const args[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return -1;
	}
	else if (pid == 0)
	{
		execvp(args[0], args);
		perror("execvp");
		_exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (status);
	}
}

