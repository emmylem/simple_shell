#include "shell.h"
#include <stdio.h>

int create_error(char **args, int err);
int len_num(int num);
char *_atos(int num);

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

/**
 * len_num - counts lengths of digit
 * @num: number to measure
 *
 * Return: digit length
 */
int len_num(int num)
{
	unsigned int Num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		Num1 = num * -1;
	}
	else
	{
		Num1 = num;
	}
	while (Num1 > 9)
	{
		len++;
		Num1 /= 10;
	}

	return (len);
}

/**
 * _atos - opposite of atoi func but this
 *           to convert integer to string
 * @num: the integer
 * Return: converted string
 */
char *_atos(int num)
{
	char *buffer;
	int len = len_num(num);
	unsigned int Num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		Num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		Num1 = num;
	}

	len--;

	while (Num1 > 0)
	{
		buffer[len] = (Num1 % 10) + '0';
		Num1 = Num1 / 10;
		len--;
	}

	return (buffer);
}
