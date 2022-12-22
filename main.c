#include "shell.h"
void shell(int ac, char **av, char **env);

/**
 * main - entyr point
 * @ac: arg count
 * @av: array
 * @env: environment
 * Return: 0;
 */
int main(int ac, char **av, char **env)
{
	if (!ac)
		(void)ac;
	if (!av)
		(void)av;
	if (!env)
		(void)env;
	shell(ac, av, env);
	return (0);
}
