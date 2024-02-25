#include "shell.h"

/**
* _myexit - exits the shell
* @info: passinfo struct
* Return: -2  on success (to exit the shell) or 0 on error
*/


int _myexit(passinfo_t *info)
{

int ret = -2;

int flag;

if (info->argv[1])
{
flag = _atoi(info->argv[1]);
if (flag < 0)
{
info->status = 2;
print_error(info, "Illegal number: ");
_puts(info->argv[1]);
_puts("\n");
return (0);
}
info->error = _atoi(info->argv[1]);
return (ret);
}
info->error = -1;
return (ret);
}

/**
* _cd - changes the current directory
* @info: passinfo struct
* Return: 1 on success, -1 on error
*/

int _cd(passinfo_t *info)
{
	char *home = get_env(info, "HOME=");

	char *oldpwd = get_env(info, "PWD=");

	char *pwd = NULL;

	int ret = 1;

	if (!info->argv[1] || _strcmp(info->argv[1], "~") == 0)
	{
		if (home)
			ret = chdir(home);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (oldpwd)
			ret = chdir(oldpwd);
	}
	else
		ret = chdir(info->argv[1]);
	if (ret == -1)
	{
		info->error = 1;
		_puts("cd: can't cd to ");
		_puts(info->argv[1]);
		_puts("\n");
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			_set_env(info, "PWD", pwd);
			free(pwd);
		}
	}
	return (ret);
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
