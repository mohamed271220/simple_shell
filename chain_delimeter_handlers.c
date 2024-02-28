#include "shell.h"

/**
* is_chained - checks if the command is chained
* @info: command
* @cmd: command
* @path: path
* Return: 1 if chained, 0 otherwise
*/
int is_chained(passinfo_t *info, char *cmd, size_t *path)
{
size_t i = *path;
if (cmd[i] == '|' && cmd[i + 1] == '|')
{
cmd[i] = 0;
i++;
info->cmdtype = CMD_OR;
}
else if (cmd[i] == '&' && cmd[i + 1] == '&')
{
cmd[i] = 0;
i++;
info->cmdtype = CMD_AND;
}
else if (cmd[i] == ';')
{
cmd[i] = 0;
info->cmdtype = CMD_PIPE;
}
else
return (0);
*path = i;
return (1);
}


/**
* exec_chained - execute chained commands
* @info: info
* @cmd: command
* @path: path
* @i: index
* @len: length
* Return: voiid
*/

void exec_chained(passinfo_t *info, char *cmd, size_t *path,
size_t i, size_t len)
{
size_t j = *path;

if (info->cmdtype == CMD_AND)
{
if (info->status)
{
cmd[i] = 0;
j = len;
}
}
if (info->cmdtype == CMD_OR)
{
if (!info->status)
{
cmd[i] = 0;
j = len;
}
}

*path = j;
}

/**
* replace_vars - replace variables
* @info: info
* Return: 1 on success, 0 on error
*/

int replace_vars(passinfo_t *info)
{
int i = 0;
list_t *tmp;

for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;

if (!_strcmp(info->argv[i], "$?"))
{
replace_str(&(info->argv[i]),
_strdup(number_conversion(info->status, 10, 0)));
continue;
}
if (!_strcmp(info->argv[i], "$$"))
{
replace_str(&info->argv[i],
_strdup(number_conversion(getpid(), 10, 0)));
continue;
}
tmp = node_starts_with(info->env, &info->argv[i][1], '=');
if (tmp)
{
replace_str(&(info->argv[i]),
_strdup(_strchr(tmp->str, '=') + 1));
continue;
}
replace_str(&info->argv[i], _strdup(""));
}
return (0);
}

/**
* replace_str - replace string
* @str: string
* @new_str: new string
* Return: 1 if success, 0 if failed
*/

int replace_str(char **str, char *new_str)
{
if (!str || !*str || !new_str)
return (0);
free(*str);
*str = new_str;
return (1);
}
