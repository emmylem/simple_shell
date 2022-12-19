#include "shell.h"
#include <stdio.h>

int create_error(char **args, int err);

/**
 * create_error - writes a error message to stderr
 * @args: array of elements
 * @err: the error value
 *
 * Return: the error value
 */
int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
		case -1:
			error = error_env(args);
			break;
		case 1:
			error = error_1(args);
			break;
		case 2:
			if (*(args[0]) == 'e')
				error = error_2_exit(++args);
			else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
				error = error_2_syntax(args);
			else
				error = error_2_cd(args);
			break;
		case 126:
			error = error_126(args);
			break;
		case 127:
			error = error_127(args);
			break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);
}
