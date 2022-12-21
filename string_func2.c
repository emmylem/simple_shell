#include "shell.h"
#include <stdio.h>

char *_strchr(char *b, char c);
int _strspn(char *b, char *accept);
int _strcmp(char *b1, char *b2);
int _strncmp(const char *b1, const char *b2, size_t n);

/**
* _strchr - locates a character in a string
* @b: string to be searched
* @c: character to be located
*
* Return: if c is found(a pointer) else (Null)
*/
char *_strchr(char *b, char c)
{
	int count;

	for (count = 0; b[count]; count++)
	{
		if (b[count] == c)
			return (b + count);
	}

	return (NULL);
}

/**
* _strspn - gets the length of prefix substring
* @b: string to be searched
* @accept: prefix to be measured
*
* Return: number of bytes in b
*/
int _strspn(char *b, char *accept)
{
	int bytes = 0;
	int count;

	while (*b)
	{
		for (count = 0; accept[count]; count++)
		{
			if (*b == accept[count])
			{
				bytes++;
				break;
			}
		}
		b++;
	}
	return (bytes);
}
/**
* _strcmp - compares two strings
* @b1: first string to be compared
* @b2: second string to be compared
*
* Return: positive or negative bytes difference
*/
int _strcmp(char *b1, char *b2)
{
	while (*b1 && *b2 && *b1 == *b2)
	{
		b1++;
		b2++;
	}

	if (*b1 != *b2)
		return (*b1 - *b2);

	return (0);
}

/**
* _strncmp - compares two string
* @b1: pointer to string
* @b2: pointer to string
* @n: first n bytes of string to compare
*
* Return: less than 0 if b1 iis shorter than b2
* 0 if b1 and b2 match
*/
int _strncmp(const char *b1, const char *b2, size_t n)
{
	size_t i;

	for (i = 0; b1[i] && b2[i] && i < n; i++)
	{
		if (b1[i] > b2[i])
			return (b1[i] - b2[i]);
		else if (b1[i] < b2[i])
			return (b1[i] - b2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
