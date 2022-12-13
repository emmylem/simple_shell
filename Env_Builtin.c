#include "shell.h"
#include <stdio.h>

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
* shellby_env - prints the current environment
* @args: array of arguments
* @front: double pointer
*
* Return:if error -l else 0
*/
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int count;
	char cu_env = '\n';

	if (environ == NULL)
		return (-1);

	for (count = 0; environ[count]; count++)
	{
		write(STDOUT_FILENO, environ[count], _strlen(environ[count]));
		write(STDOUT_FILENO, &cu_env, 1);
	}
	(void)args;
	return (0);
}

/**
* shellby_setenv - changes or adds new environment
* @args: array of arguments
* @front: double pointer
* descip: args[1] the existing path , args[2] value of new var
* Return: if error -1 else 0
*/
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int count;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(args, -1));
	}
	for (count = 0; environ[count]; count++)
		new_environ[count] = environ[count];

	free(environ);
	environ = new_environ;
	environ[count] = new_value;
	environ[count + 1] = NULL;

	return (0);
}

/**
* shellby_unsetenv - deletes an environment variable from path
* @args: an array of arguments
* @front: double pointer
*
* Return: -1 if error else 0
*/
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	ssize_t size;
	int count, count2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));

	for (count = 0, count2 = 0; environ[count]; count++)
	{
		if (*env_var == environ[count])
		{
			free(*env_var);
			continue;
		}
		new_environ[count2] = environ[count];
		count2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
