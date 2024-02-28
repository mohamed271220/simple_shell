#include "shell.h"

/**
* is_sh_mode - checks if the shell is in interactive mode
* @info : pointer to passinfo_t struct containing shell info
* Return: 1 if shell is in interactive mode, 0 if not
*/
int is_sh_mode(passinfo_t *info)
{
return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
* is_delim - checks if a character is a delimiter
* @c: character to be checked
* @delim: string containing delimiters
* Return: 1 if character is a delimiter, 0 if not
*/

int is_delim(char c, char *delim)
{
while (*delim)
{
if (c == *delim++)
return (1);
}
return (0);
}

/**
* _isAlpha - checks if a character is an alphabet
* @c: character to be checked
* Return: 1 if character is an alphabet, 0 if not
*/

int _isAlpha(char c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
return (0);
}

/**
* _atoi - converts a string to an integer
* @s: string to be converted
* Return: the integer value of the string
*/

int _atoi(char *s)
{
int i, sign = 1, fg = 0, ret;
unsigned int result = 0;

for (i = 0;  s[i] != '\0' && fg != 2; i++)
{
if (s[i] == '-')
sign *= -1;

if (s[i] >= '0' && s[i] <= '9')
{
fg = 1;
result *= 10;
result += (s[i] - '0');
}
else if (fg == 1)
fg = 2;
}

if (sign == -1)
ret = -result;
else
ret = result;

return (ret);
}

/**
* _erratoi - converts a string to an integer
* @s: string to be converted
* Return: the integer value of the string or -1
*/
int _erratoi(char *s)
{
int i = 0;
unsigned long int ret = 0;

if (*s == '+')
s++;
for (i = 0;  s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
ret *= 10;
ret += (s[i] - '0');
if (ret > INT_MAX)
return (-1);
}
else
return (-1);
}
return (ret);
}
