#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

extern char **environ;

int execute_command(char *const args[])
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
		return status;
	}
}

void process_input(char *input_str)
{
	char *token;
	char **args = NULL;
	int arg_count = 0;
	int exit_status = -1;
	int i;

	token = strtok(input_str, " ");
	while (token != NULL)
	{
		if (strcmp(token, "$?") == 0)
		{
			char exit_status_str[4];
			snprintf(exit_status_str, sizeof(exit_status_str), "%d", exit_status);
			args = realloc(args, (arg_count + 1) * sizeof(char *));
			args[arg_count] = strdup(exit_status_str);
		}
		else if (strcmp(token, "$$") == 0)
		{
			char pid_str[10];
			snprintf(pid_str, sizeof(pid_str), "%d", getpid());
			args = realloc(args, (arg_count + 1) * sizeof(char *));
			args[arg_count] = strdup(pid_str);
		}
		else
		{
			args = realloc(args, (arg_count + 1) * sizeof(char *));
			args[arg_count] = strdup(token);
		}
		arg_count++;
		token = strtok(NULL, " ");
	}

	if (arg_count > 0)
	{
		args = realloc(args, (arg_count + 1) * sizeof(char *));
		args[arg_count] = NULL;
		exit_status = execute_command(args);
		for (i = 0; i <= arg_count; i++)
		{
			free(args[i]);
		}
		free(args);
		args = NULL;
		arg_count = 0;
	}
}

void execute_shell(void)
{
	char *input_str = NULL;
	size_t input_size = 0;
	ssize_t char_num;

	while (1)
	{
		if (isatty(fileno(stdin)))
		{
			write(1, "$ ", 2);
		}

		char_num = getline(&input_str, &input_size, stdin);
		if (char_num == -1)
		{
			break;
		}
		else
		{
			input_str[strcspn(input_str, "\n")] = '\0';
			if (strcmp(input_str, "exit") == 0)
			{
				break;
			}

			process_input(input_str);
		}
	}

	free(input_str);
}

int main(void)
{
	execute_shell();
	return 0;
}
