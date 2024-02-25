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
	size_t path_size = *path;
	size_t cmd_len = _strlen(cmd);

	if (path_size < cmd_len && path_size + 1 < cmd_len)
	{
		if (cmd[path_size] == '|' && cmd[path_size + 1] == '|')
		{
			cmd[path_size] = 0;
			path_size += 1;
			info->cmdtype =  CMD_OR;
		}
		else if (cmd[path_size] == '&' && cmd[path_size + 1] == '&')
		{
			cmd[path_size] = 0;
			path_size += 1;
			info->cmdtype =  CMD_AND;
		}
		else if (cmd[path_size] == ';')
		{
			cmd[path_size] = 0;
			info->cmdtype =  CMD_NORMAL;
		}
		else if (cmd[path_size] == '|')
		{
			cmd[path_size] = 0;
			info->cmdtype =  CMD_PIPE;
		}
		else
		{
			info->cmdtype =  CMD_NORMAL;
			return (0);
		}
		*path = path_size;
		return (1);
	}
	return (0);
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
size_t path_size = *path;
if (info->cmdtype == CMD_OR)
{
if (!info->status)
{
cmd[i] = 0;
path_size = len;
}

}
else if (info->cmdtype == CMD_AND)
{
if (info->status)
{
cmd[i] = 0;
path_size = len;
}
}
*path = path_size;
}

/**
* replace_vars - replace variables
* @info: info
* Return: 1 on success, 0 on error
*/

int replace_vars(passinfo_t *info)
{
int i = 0;

list_t *node;
for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;
if (!_strcmp(info->argv[i], "$?"))
{
replace_str(&info->argv[i],
_strdup(number_conversion(info->status, 10, 0)));
continue;
}
else if (!_strcmp(info->argv[i], "$$"))
{
replace_str(&info->argv[i],
_strdup(number_conversion(getpid(), 10, 0)));
continue;
}
node = node_starts_with(info->env, &info->argv[i][1], '=');
if (node)
{
replace_str(&info->argv[i], _strdup(_strchr(node->str, '=') + 1));
continue;
}
replace_str(&info->argv[i], _strdup(""));
}
return (1);
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
