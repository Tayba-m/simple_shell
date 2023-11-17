#include "shell.h"

/**
 * exec_com - function to execute command
 * @args: arguments list
 * Return: exit status, -1 otherwise
 */

int exec_com(char *const args[])
{
	pid_t pi_d;
	int stat_us;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return -1;
	}
	else if (pi_d == 0)
	{
		execvp(args[0], args);
		perror("execvp");
		_exit(1);
	}
	else
	{
		waitpid(pi_d, &stat_us, 0);
		return (stat_us);
	}
}

