#include "shell.h"
#include <stdio.h>

void *_realloc(void *ptr, unsigned int new_size, unsigned int old_size);
void assign_lineptr(char **lineptr, size_t *b, char *buffer, size_t n);
ssize_t _getline(char **lineptr, size_t *b, FILE *stream);

/**
* _realloc - reallocates a memory block using malloc and free
* @ptr: a pointer to memory previously allocated
* @old_size: size in bytes allocated for ptr
* @new_size: size in bytes allocated for new memory block
* Return:if new_size == oldsize - ptr
*/
void *_realloc(void *ptr, unsigned int new_size, unsigned int old_size)
{
	char *mem;
	char *ptr_copy, *fill;
	unsigned int count;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (!mem)
			return (NULL);

		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	fill = mem;

	for (count = 0; count < new_size && count < old_size; count++)
		fill[count] = *ptr_copy++;

	free(ptr);
	return (mem);
}

/**
* assign_lineptr - reassignes the lineptr var for _getline
* @lineptr: a buffer to store input string
* @b: size of lineptr
* @buffer: string to assign to lineptr
* @n: size of buffer
*/
void assign_lineptr(char **lineptr, size_t *b, char *buffer, size_t n)
{
	if (*lineptr == NULL)
	{
		if (n > 120)
			*b = n;
		else
			*b = 120;
		*lineptr = buffer;
	}
	else if (*b < n)
	{
		if (n > 120)
			*b = n;
		else
			*b = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
* _getline - reads input from a string
* @lineptr:  buffer to store input
* @b: size of lineptr
* @stream: stream to read from
* Return: number of bytes to read
*/
ssize_t _getline(char **lineptr, size_t *b, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineptr(lineptr, b, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}

