#include "shell.h"

/**
* hsh - main shell loop
* @info: passinfo struct
* @argv: arguments
* Return: 0 on success, 1 on error
*/

int hsh(passinfo_t *info, char **argv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear(info);
		if (is_sh_mode(info))
			_puts("$ ");
		_eputchar(BUFFER_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, argv);
			builtin_ret = find_built_in(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (is_sh_mode(info))
			_putchar('\n');
		free_info(info, 0);
	}
	w_history(info);
	free_info(info, 1);
	if (!is_sh_mode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->error == -1)
			exit(info->status);
		exit(info->error);
	}
	return (builtin_ret);
}

/**
* find_built_in - find built in
* @info: info
* Return: 0 on success, -1 on error, -2 on exit
*/

int find_built_in(passinfo_t *info)
{
int i, ret = -1;

builtins_t builtins[] = {
{"exit", _myexit},
{"env", print_env},
{"setenv", set_env},
{"unsetenv", remove_env},
{"cd", _cd},
{"alias", _alias},
{"history", show_history},
{"help", _help},
{NULL, NULL}
};

for (i = 0; builtins[i].name; i++)
{
if (_strcmp(info->argv[0], builtins[i].name) == 0)
{
info->line++;
ret = builtins[i].func(info);
break;
}
}

return (ret);
}

/**
* find_cmd - find command
* @info: info
* Return: void
*/

void find_cmd(passinfo_t *info)
{
char *path = NULL;

int i, k;

info->path = info->argv[0];

if (info->line_flag == 1)
{
info->line++;
info->line_flag = 0;
}

for (i = 0, k = 0; info->arg[i]; i++)
if (!is_delim(info->arg[i], " \t\n"))
k++;

if (!k)
return;

path = find_path(info, get_env(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((is_sh_mode(info) || get_env(info, "PATH=")
|| info->argv[0][0] == '/') && is_executable(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
print_error(info, "not found\n");
info->status = 127;
}
}
}

/**
* fork_cmd - fork command
* @info: info
* Return: void
*/

void fork_cmd(passinfo_t *info)
{
pid_t pid;

pid = fork();
if (pid == -1)
{
_eputs("Error: fork failed\n");
return;
}
if (pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}
