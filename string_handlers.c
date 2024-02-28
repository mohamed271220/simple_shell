#include "shell.h"

/**
* _strlen - returns the length of a string
* @s: string to be measured
* Return: length of the string
*/

int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;
	return (i);
}

/**
* _strdup - returns a pointer to a newly allocated space in memory
* which contains a copy of the string given as a parameter
* @str: string to be copied
* Return: pointer to the duplicated string
*/

char *_strdup(char *str)
{
int len = 0;
char *dup;
if (str == NULL)
return (NULL);
while (str[len])
len++;
dup = malloc(sizeof(char) * (len + 1));
if (!dup)
return (NULL);
for (len++; len--;)
dup[len] = *--str;
return (dup);

}

/**
* _strcmp - compares two strings
* @s1: first string
* @s2: second string
* Return: 0 if strings are equal, -1 if s1 < s2, 1 if s1 > s2
*/

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);

}


/**
* _strcpy - copies the string pointed to by src, including the
* terminating null byte, to the buffer pointed to by dest
* @dest: destination string
* @src: source string
* Return: pointer to the resulting string dest
*/

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
