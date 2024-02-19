#include "shell.h"

/**
* is_sh_mode - checks if the shell is in interactive mode
* @info : pointer to passinfo_t struct containing shell info
* Return: 1 if shell is in interactive mode, 0 if not
*/
int is_sh_mode(passinfo_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
* is_delim - checks if a character is a delimiter
* @c: character to be checked
* @delim: string containing delimiters
* Return: 1 if character is a delimiter, 0 if not
*/

int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (c == *delim++)
			return (1);
	}
	return (0);
}

/**
* _isAlpha - checks if a character is an alphabet
* @c: character to be checked
* Return: 1 if character is an alphabet, 0 if not
*/

int _isAlpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
* _atoi - converts a string to an integer
* @s: string to be converted
* Return: the integer value of the string
*/

int _atoi(char *s)
{
	int sign = 1;

	unsigned int num = 0;

	while (*s)
	{
		if (*s == '-')
			sign *= -1;
		if (*s >= '0' && *s <= '9')
			num = num * 10 + (*s - '0');
		else if (num > 0)
			break;
		s++;
	}
	return (sign * num);
}

/**
* _erratoi - converts a string to an integer
* @s: string to be converted
* Return: the integer value of the string or -1
*/

int _erratoi(char *s)
{
	int sign = 1;

	unsigned long int num = 0;

	while (*s)
	{
		if (*s == '-')
			sign *= -1;
		if (*s >= '0' && *s <= '9')
			num = num * 10 + (*s - '0');
		else if (num > INT_MAX)
			return (-1);
		s++;
	}
	return (sign * num);
}
