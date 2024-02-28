#include "shell.h"

/**
* clear - clears the screen
* @info: passinfo struct
* Return: void
*/

void clear(passinfo_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->argc = 0;
info->path = NULL;
}

/**
* set_info - sets the passinfo struct
* @info: passinfo struct
* @argv: argument vector
*/

void set_info(passinfo_t *info, char **argv)
{
int i = 0;

info->file_name = argv[0];
if (info->arg)
{
info->argv = _strtow(info->arg, " \t");
info->argc = i;
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv[i]; i++)
;
info->argc = i;
set_alias(info, info->argv[0]);
replace_vars(info);
}
}

/**
* free_info - frees the passinfo struct
* @info: passinfo struct
* @free_env: free environment
* Return: void
*/

void free_info(passinfo_t *info, int free_env)
{
_free(info->argv);
info->argv = NULL;
info->argc = 0;
if (free_env)
{
if (!info->env)
free_list(&(info->env));
if (!info->cmd)
free(info->arg);
if (!info->history)
free_list(&(info->history));
if (!info->alias)
free_list(&(info->alias));
_free(info->environ);
info->environ = NULL;
_free2((void **)info->cmd);
if (info->read_fd > 2)
close(info->read_fd);
_putchar(BUFFER_FLUSH);
}
}
