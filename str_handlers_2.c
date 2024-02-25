#include "shell.h"

/**
* starts_with - checks if a string starts with a given prefix
* @s: string to be checked
* @start: prefix to be checked
* Return: prefix, 0 otherwise
*/


char *starts_with(char *s, char *start)
{
while (*start)
{
if (*start != *s)
	return (0);
start++;
s++;
}
	return ((char *)start);
}


/**
* _strchr - locates a character in a string
* @s: string to be checked
* @c: character to be located
* Return: pointer to the first occurrence of the character c in the string s
*/

char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
		return (s);
		s++;
	}
	return (0);
}

/**
* _strncpy - copies a string
* @dest: destination string
* @src: source string
* @n: number of bytes to be copied
* Return: pointer to the resulting string
*/

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for ( ; i < n; i++)
		dest[i] = '\0';
	return (dest);
}



/**
* _strtow - splits a string into words
* @str: string to be split
* @delim: delimiter character
* Return: pointer to an array of strings
*/

char **_strtow(char *str, char delim)
{
	int i, j, k, n, len;

	char **words;

	len = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != delim)
		{
			len++;
			for ( ; str[i] != delim && str[i] != '\0'; i++)
				;
		}
	}
	words = malloc(sizeof(char *) * (len + 1));
	if (words == NULL)
		return (NULL);
	for (i = 0, j = 0; j < len; i++)
	{
		if (str[i] != delim)
		{
			n = 0;
			for (k = i; str[k] != delim && str[k] != '\0'; k++)
				n++;
			words[j] = malloc(sizeof(char) * (n + 1));
			if (words[j] == NULL)
			{
				for (j--; j >= 0; j--)
					free(words[j]);
				free(words);
				return (NULL);
			}
			for (k = 0; k < n; k++, i++)
				words[j][k] = str[i];
			words[j][k] = '\0';
			j++;
		}
	}
	words[j] = NULL;
	return (words);
}
