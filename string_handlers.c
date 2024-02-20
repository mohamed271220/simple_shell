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
    char *dup;
    int i, len;

    if (str == NULL)
        return (NULL);
    len = _strlen(str);
    dup = malloc(sizeof(char) * (len + 1));
    if (dup == NULL)
        return (NULL);
    for (i = 0; i < len; i++)
        dup[i] = str[i];
    dup[i] = '\0';
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
    int i;

    for (i = 0; s1[i] == s2[i]; i++)
    {
        if (s1[i] == '\0')
            return (0);
    }
    return (s1[i] - s2[i]);
}

/**
* _strcat - concatenates two strings
* @dest: destination string
* @src: source string
* Return: pointer to the resulting string
*/

char *_strcat(char *dest, char *src)
{
    int i, j;

    for (i = 0; dest[i] != '\0'; i++)
        ;
    for (j = 0; src[j] != '\0'; j++)
    {
        dest[i] = src[j];
        i++;
    }
    dest[i] = '\0';
    return (dest);
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
