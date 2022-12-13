#include "shell.h"
#include <stdio.h>

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
* _copyenv - creates a copy of the environment
*
* Return: Null if error or pointer
*/
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int count;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (count = 0; environ[count]; count++)
	{
		new_environ[count] = malloc(_strlen(environ[count]) + 1);

		if (!new_environ[count])
		{
			for (count--; count >= 0; count--)
				free(new_environ[count]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[count], environ[count]);
	}
	new_environ[count] = NULL;

	return (new_environ);
}

/**
* free_env - frees the environment and copy
*/
void free_env(void)
{
	int count;

	for (count = 0; environ[count]; count++)
		free(environ[count]);
	free(environ);
}

/**
* _getenv - gets the environmental variable
* @var: name of the environmental variable
* Return: Null if it doesn't exit or pointer
*/
char **_getenv(const char *var)
{
	int count, len;

	len = _strlen(var);
	for (count = 0; environ[count]; count++)
	{
		if (_strncmp(var, environ[count], len) == 0)
			return (&environ[count]);
	}
	return (NULL);
}
