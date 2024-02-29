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
* print_decimal - prints a decimal number (base 10)
* @n: number to be printed
* @fd: file descriptor
* Return: void
*/

int print_decimal(int n, int fd)
{
int (*__putchar)(char) = _putchar;
int i, count = 0;
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (n < 0)
{
_abs_ = -n;
__putchar('-');
count++;
}
else
_abs_ = n;
current = _abs_;
for (i = 1000000000; i > 1; i /= 10)
{
if (_abs_ / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
}
__putchar('0' + current);
count++;

return (count);
}

/**
* number_conversion - converts a number to a string
* @num: number to be converted
* @base: base of the number
* @flag: flag to indicate if the number is signed
* Return: pointer to the resulting string
*/

char *number_conversion(long int num, int base, int flag)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (flag == 1 && base == 10 && num < 0)
{
sign = '-';
n = -num;
}
array = flag & CONVER_TO_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do {
*--ptr = array[n % base];
n /= base;
} while (n != 0);
if (sign)
*--ptr = sign;
return (ptr);
}


/**
* remove_comments - removes comments from a string
* @str: string to be processed
* Return: void
*/

void remove_comments(char *str)
{
int i;

for (i = 0; str[i] != '\0'; i++)
if (str[i] == '#' && (!i || str[i - 1] == ' '))
{
str[i] = '\0';
break;
}
}
