#include "shell.h"

/**
* _eputs - prints a string to the standard error output
* @str: string to be printed
* Return: void
*/

void _eputs(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		_eputchar(str[i]);
	}
}

/**
* _eputchar - writes a character to the standard error output
* @c: character to be written
* Return: on success 1, on error -1
*/

int _eputchar(char c)
{
static int i;

static char buf[WRITE_BUFFER];

if (c == BUFFER_FLUSH || i >= WRITE_BUFFER)
{
write(2, buf, i);
i = 0;
}
if (c != BUFFER_FLUSH)
buf[i++] = c;
return (1);
}

/**
* _putfd - writes a character to a file descriptor
* @fd: file descriptor
* @c: character to be written
* Return: on success 1, on error -1
*/

int _putfd(int fd, char c)
{
static int i;

static char buf[WRITE_BUFFER];

if (c == BUFFER_FLUSH || i >= WRITE_BUFFER)
{
write(fd, buf, i);
i = 0;
}
if (c != BUFFER_FLUSH)
buf[i++] = c;
return (1);
}

/**
* _putsfd - writes a string to a file descriptor
* @fd: file descriptor
* @str: string to be written
* Return: number of characters written
*/

int _putsfd(int fd, char *str)
{
	int i = 0;

	if (str == NULL)
	{
		return (0);
	}
	while (str[i])
	{
		_putfd(fd, str[i]);
		i++;
	}
	return (i);
}
