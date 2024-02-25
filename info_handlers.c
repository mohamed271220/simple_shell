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
info->argv = _strtow(info->arg, '\t');
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
(void)free_env;
if (info->arg)
free(info->arg);
if (info->argv)
free(info->argv);
if (info->path)
free(info->path);
if (info->env_changed)
free_list(&info->env);
if (info->alias)
free_list(&info->alias);
if (info->cmd)
free(info->cmd);
if (info->history)
free_list(&info->history);

clear(info);
}
