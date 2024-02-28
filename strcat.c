#include "shell.h"

/**
* _strcat - concatenates two strings
* @dest: destination string
* @src: source string
* Return: pointer to the resulting string
*/

char *_strcat(char *dest, char *src)
{
char *hold = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (hold);
}

/**
* _strncat - concatenates two strings up to n bytes
* @dest: destination string
* @src: source string
* @n: maximum number of bytes to be copied
* Return: pointer to the resulting string
*/
char *_strncat(char *dest, char *src, int n)
{
int i, j;
for (i = 0; dest[i] != '\0'; i++)
;
for (j = 0; src[j] != '\0' && j < n; j++)
{
dest[i + j] = src[j];
}
dest[i + j] = '\0';
return (dest);
}
