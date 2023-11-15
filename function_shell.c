i#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

/**
 * execute_exit - his function is responsible for exiting the shell program.
 * @void : it calls the exit() function .
 * Return: 0
 */
void execute_exit(void)
{
	exit(EXIT_SUCCESS);
}

/**
 * execute_env - This function prints the environment variables.
 * @void : it uses the environ variable.
 * Return: 0
 */
void execute_env(void)
{
	extern.c char **environ;
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, sizeof(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * execute_cd - his function changes the current working diroctory.
 * @args : it attempts to change the directory to the home directory.
 *
 * Return: 0
 */
void execute_cd(char **args)
{
	if (args[1] == NULL)
	{
		char *home_dir = getenv("HOME");

		if (home_dir != NULL)
		{
			if (chdir(home_dir) != 0)
			{
				write(STDERR_FILENO, "cd: failed to change directory\n", 31);
			}
		}
		else
		{
			write(STDERR_FILENO, "cd: no home directory found\n", 28);
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			write(STDERR_FILENO, "cd: failed to change directory\n", 31);
		}
	}
}

/**
 * str_equal - This function compares two strings to check if they are equal.
 * @str1 : this is string one to checker.
 * @str2 : this is string tow to checker.
 *
 * Return:0
 */
int str_equal(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 == '\0' && *str2 == '\0');
}

/**
 * execute_int_command - This function executes internal commands.
 * @args :It compares the first argument (args[0]) with predefined command.
 *
 * Return :0
 */
void execute_int_command(char **args)
{
	char *exit_cmd = "exit";
	char *env_cmd = "env";
	char *cd_cmd = "cd";

	if (str_equal(args[0], exit_cmd))
	{
		execute_exit();
	}
	else if (str_equal(args[0], env_cmd))
	{
		execute_env();
	}
	else if (str_equal(args[0], cd_cmd))
	{
		execute_cd(args);
	}
}
