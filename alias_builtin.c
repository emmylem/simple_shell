#include "shell.h"
#include <stdio.h>

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - builtin command that prints all aliases
 * @args: array of argument
 * @front: a double pointer
 * Return: if error -1 else 0
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *tmp = aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (tmp)
		{
			print_alias(tmp);
			tmp = tmp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		tmp = aliases;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (tmp)
			{
				if (_strcmp(args[i], tmp->name) == 0)
				{
					print_alias(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				ret = create_error(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (ret);
}

/**
 * set_alias - set existing alias 'name' with new value
 * or creates a new value with 'name'
 * @var_name: nmae of new alias
 * @value: value pf the alias first character is '='
 */
void set_alias(char *var_name, char *value)
{
	alias_t *tmp = aliases;
	int len, j, n;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, n = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[n++] = value[j];
	}
	new_value[n] = '\0';
	while (tmp)
	{
		if (_strcmp(var_name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = new_value;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - prints alias in format name='value'
 * @alias: pointer to an alias
 * Return: 0
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
