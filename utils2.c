#include "shell.h"


/**
* print_error - prints error message
* @info: pointer to passinfo_t struct containing shell info
* @msg: error message to be printed
* Return: void
*/

void print_error(passinfo_t *info, char *msg)
{
	_eputs(info->file_name);
	_eputs(": ");
	print_decimal(info->line, STDIN_FILENO);
	_eputs(": ");
_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(msg);
}


/**
* print_decimal - prints a decimal number
* @n: number to be printed
* @fd: file descriptor
* Return: void
*/

void print_decimal(unsigned int n, int fd)
{
	unsigned int num = n;

	unsigned int div = 1;

	char c;

	while (num / div > 9)
		div *= 10;
	while (div)
	{
		c = (num / div) + '0';
		write(fd, &c, 1);
		num %= div;
		div /= 10;
	}
}
