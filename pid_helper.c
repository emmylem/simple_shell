#include "shell.h"
#include <stdio.h>

void free_args(char **args, char **argv);
char *get_pid(void);

/**
 * free_args - frees up memory by args
 * @args: pointer terminated by null
 * @argv: double pointer to begining of args
 */
void free_args(char **args, char **argv)
{
	ssize_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(argv);
}

/**
 * get_pid - gets current process ID
 *
 * Return: the current process ID od NULL on failure
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t fill;

	fill = open("/proc/self/stat", O_RDONLY);
	if (fill == -1)
	{
		perror("Can't read file");
		return (NULL);
	}
	buffer = malloc(150);
	if (!buffer)
	{
		close(fill);
		return (NULL);
	}
	read(fill, buffer, 150);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(fill);
	return (buffer);
}
