#include "shell.h"
#include <stdio.h>

int _strlen(const char *b);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);

/**
* _strlen - returns length of string
* @b: pointer to the character string
*
* Return: the length of string
*/
int _strlen(const char *b)
{
	int len = 0;

	if (b)
		return (len);
	for (len = 0; b[len]; len++)
		;
	return (len);
}

/**
* _strcpy - copies string pointed to src
* @dest: pointer to destination of copied string
* @src: pointer to src of string
*
* Return: pointer to dest
*/
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
* _strcat - concatenates two strings
* @dest: pointer to destination string
* @src: pointer to source string
*
* Return: pointer to destination string
*/
char *_strcat(char *dest, const char *src)
{
	char *new_dest = '\0';
	const char *new_src;

	new_dest = dest;
	new_src = src;

	while (*new_dest != '\0')
		new_dest++;

	while (*new_src != '\0')
		*new_dest++ = *new_src++;
	*new_dest = '\0';
	return (dest);
}

/**
* _strncat - concatenates two strings where
*n number of bytes will be copied
* @dest: pointer to destination string
* @src: pointer to source string
* @n: n bytes to copy from src
*
* Return: pointer to destination string
*/
char *_strncat(char *dest, const char *src, size_t n)
{
	ssize_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
