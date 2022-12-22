#include "shell.h"
#include <stdio.h>

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - locates the delimeter of the first token
 *    in astring
 * @str: string to be searche
 * @delim: delimeter character
 *
 * Return:the delimeter index of token in str
 */
int token_len(char *str, char *delim)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		len++;
		index++;
	}

	return (len);
}

/**
 * count_tokens - counts number of delimited words
 * @str: strig yo be searched
 * @delim: delimeter character
 *
 * Return: number of words contained within str
 */
int count_tokens(char *str, char *delim)
{
	int count, tokens = 0, len = 0;

	for (count = 0; *(str + count); count++)
		len++;

	for (count = 0; count < len; count++)
	{
		if (*(str + count) != *delim)
		{
			tokens++;
			count += token_len(str + count, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - tokenizes a sting
 * @line: the string
 * @delim: delimeter character to tokenize string
 * Return: a pointer to array
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int count = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[count] == *delim)

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		ptr[t] = malloc(sizeof(letters));
		if (!ptr[t])
		{
			for (count -= 1; count >= 0; count--)
				free(ptr[count]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[count];
			count++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
