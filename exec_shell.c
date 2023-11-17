#include "shell.h"

/**
 * exec_shell - function execute shell
 *
 * Return: nothing
 */
void exec_shell(void)
{
	char *input_str = NULL;
	size_t input_size = 0;
	ssize_t num_char;

	while (1)
	{
		if (isatty(fileno(stdin)))
		{
			printf("$");
		}

		num_char = getline(&input_str, &input_size, stdin);
		if (num_char == -1)
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
