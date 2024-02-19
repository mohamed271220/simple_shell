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
char *a = s;
while (n--)
*s++ = b;
return (a);
}

/**
* _free - frees a double pointer
* @ptr: pointer to be freed
* Return: void
*/

void _free(char **ptr)
{
char **temp = ptr;
if (ptr == NULL)
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
void *new_ptr;
if (new_size == old_size)
return (ptr);
if (ptr == NULL)
{
new_ptr = malloc(new_size);
if (new_ptr == NULL)
return (NULL);
return (new_ptr);
}

if (new_size == 0 && ptr != NULL)
{
free(ptr);
return (NULL);
}

new_ptr = malloc(new_size);
if (new_ptr == NULL)
return (NULL);
if (new_size > old_size)
_memcpy(new_ptr, ptr, old_size);
else
_memcpy(new_ptr, ptr, new_size);
free(ptr);
return (new_ptr);
}

/**
* _free2 - frees a double pointer and NULLs it
* @ptr: double pointer to be freed
* Return: 1 if success, 0 if failed
*/

int _free2(char **ptr)
{
if (ptr == NULL)
return (0);
free(*ptr);
ptr = NULL;
return (1);
}
