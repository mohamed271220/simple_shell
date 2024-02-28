#include "shell.h"

/**
* _myexit - exits the shell
* @info: passinfo struct
* Return: -2  on success (to exit the shell) or 0 on error
*/


int _myexit(passinfo_t *info)
{

int exit_status = 0;
if (info->argv[1])
{
exit_status = _erratoi(info->argv[1]);
if (exit_status == -1)
{
info->error = 2;
print_error(info, "exit: Illegal number: ");
_puts(info->argv[1]);
_puts("\n");
return (1);
}
info->error = _erratoi(info->argv[1]);
return (-2);
}
info->error = -1;
return (-2);
}

/**
* _cd - changes the current directory
* @info: passinfo struct
* Return: 1 on success, -1 on error
*/

int _cd(passinfo_t *info)
{
char *s, *dir, buffer[1024];
int ret;
s = getcwd(buffer, 1024);
if (!s)
_puts("Error getting current directory\n");
if (!info->argv[1])
{
dir = get_env(info, "HOME=");
if (!dir)
ret = chdir((dir = get_env(info, "PWD=")) ? dir : "/");
else
ret = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!get_env(info, "OLDPWD="))
{
_puts(s);
_puts("\n");
return (1);
}
_puts(get_env(info, "OLDPWD=")), _puts("\n");
ret = chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
}
else
ret = chdir(info->argv[1]);
if (ret == -1)
{
print_error(info, "cd: can't cd to ");
_eputs(info->argv[1]);
_eputchar('\n');
}
else
{
_set_env(info, "OLDPWD", get_env(info, "PWD="));
_set_env(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}


/**
* _help - prints the help
* @info: passinfo struct
* Return: 0
*/

int _help(passinfo_t *info)
{
	char **help;

	help = info->argv;
	_puts("This is a simple shell\n");
	_puts("Type a command and press enter.\n");
	_puts("The following commands are built in:\n");
	_puts("cd\n");
	_puts("exit\n");
	_puts("help\n");
	_puts("history\n");
	_puts("alias\n");
	_puts("env\n");
	_puts("setenv\n");
	if (0)
	{
	_puts(*help);
	}
	return (0);
}

/**
* show_history - prints the history
* @info: passinfo struct
* Return: 1 on success, 0 on error
*/

int show_history(passinfo_t *info)
{
print_list(info->history);
return (1);
}

/**
* show_alias - prints the alias
* @info: passinfo struct
* Return: 1 on success, 0 on error
*/

int show_alias(passinfo_t *info)
{
print_list(info->alias);
return (1);
}
