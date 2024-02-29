#include "shell.h"

/**
* _memset - fills memory with a constant byte
* @s: pointer to the memory area
* @b: the constant byte
* @n: the number of bytes to be filled
* Return: a pointer to the memory area s
*/

char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;

for (i = 0; i < n; i++)
s[i] = b;
return (s);
}

/**
* _free - frees a double pointer
* @ptr: pointer to be freed
* Return: void
*/

void _free(char **ptr)
{
char **temp = ptr;

if (!ptr)
return;
while (*ptr)
free(*ptr++);
free(temp);
}

/**
* _memcpy - copies memory area
* @dest: pointer to the destination memory area
* @src: pointer to the source memory area
* @n: the number of bytes to be copied
* Return: a pointer to the destination memory area
*/

void *_memcpy(void *dest, const void *src, unsigned int n)
{
char *d = dest;
const char *s = src;
while (n--)
*d++ = *s++;
return (dest);
}

/**
* _realloc - reallocates a memory block using malloc and free
* @ptr: pointer to the memory previously allocated
* @old_size: size of the allocated space for ptr
* @new_size: new size for the new memory block
* Return: a pointer to the new memory block
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
	return (p);
}

/**
* _free2 - frees a double pointer and NULLs it
* @ptr: double pointer to be freed
* Return: 1 if success, 0 if failed
*/

int _free2(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
