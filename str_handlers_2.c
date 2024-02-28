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
if (*start++ != *s++)
return (NULL);
return ((char *)s);
}


/**
* _strchr - locates a character in a string
* @s: string to be checked
* @c: character to be located
* Return: pointer to the first occurrence of the character c in the string s
*/

char *_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');
return (NULL);
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

char **_strtow(char *str, char *delim)
{
int i, j, k, m, num_words = 0;
char **words;
if (str == NULL || str[0] == 0)
return (NULL);
if (!delim)
delim = " ";
for (i = 0; str[i]; i++)
if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
num_words++;

if (num_words == 0)
return (NULL);

words = malloc(sizeof(char *) * (num_words + 1));
if (words == NULL)
return (NULL);
for (i = 0, j = 0; j < num_words; j++)
{
while (is_delim(str[i], delim))
i++;
k = 0;
while (!is_delim(str[i + k], delim) && str[i + k])
k++;
words[j] = malloc((k + 1) * sizeof(char));
if (words[j] == NULL)
{
for (k = 0; k < j; k++)
free(words[k]);
free(words);
return (NULL);
}
for (m = 0; m < k; m++)
words[j][m] = str[i++];
words[j][m] = 0;
}
words[j] = NULL;
return (words);
}
