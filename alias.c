#include "shell.h"

/**
* set_alias - sets an alias
* @info: passinfo struct
* @name: name of the alias
* Return: 1 on success, -1 on error
*/

int set_alias(passinfo_t *info, char *name)
{
char *alias_name;

alias_name = _strchr(name, '=');
if (!alias_name)
{
	return (-1);
}
if (!*++alias_name)
{
	return (remove_alias(info, name));
}
remove_alias(info, name);
return (add_node_end(&info->alias, name, 0) == NULL);
}


/**
* remove_alias - removes an alias
* @info: passinfo struct
* @name: name of the alias
* Return: 1 on success, 0 on error
*/

int remove_alias(passinfo_t *info, char *name)
{
char *alias_name = NULL, c;

int ret;

alias_name = _strchr(name, '=');
if (alias_name)
{
c = *alias_name;
*alias_name = 0;
ret = delete_node_at_index(&info->alias,
node_by_index(info->alias, node_starts_with(info->alias, name, -1)));
*alias_name = c;
return (ret);
}
return (0);
}

/**
* print_alias - prints the alias
* @node: node list
* Return: 1 on success, 0 on error
*/

int print_alias(list_t *node)
{
char *alias = NULL;

char *alias_name = NULL;

if (node)
{
alias = _strchr(node->str, '=');
for (alias_name = node->str; alias_name < alias; alias_name++)
_putchar(*alias_name);
_putchar('/');
_puts(alias + 1);
_put('\n');
return (1);
}
return (0);
}


/**
* _alias - prints the alias
* @info: info list
* Return: 1 on success, 0 on error
*/

int _alias(passinfo_t *info)
{
int i = 0;

char *alias = NULL;

list_t *temp = NULL;
if (info->argc == 1)
{
	temp = info->alias;
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
return (1);
}
for (i = 1; i < info->argc; i++)
{
	alias = _strchr(info->argv[i], '=');
	if (alias)
		set_alias(info, info->argv[i]);
	else
		print_alias(node_starts_with(info->alias, info->argv[i], "="));
}

return (1);
}
