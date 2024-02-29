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
char *p, c;
int ret;
p = _strchr(name, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_at_index(&info->alias,
node_by_index(info->alias, node_starts_with(info->alias, name, -1)));
*p = c;
return (ret);
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
_putchar('\'');
_puts(alias + 1);
_putchar('\n');
return (0);
}
return (1);
}


/**
* _alias - prints the alias
* @info: info list
* Return: 0
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
return (0);
}
for (i = 1; info->argv[i]; i++)
{
alias = _strchr(info->argv[i], '=');
if (alias)
set_alias(info, info->argv[i]);
else
print_alias(node_starts_with(info->alias, info->argv[i], '='));
}
return (0);
}

/**
* change_alias - changes an alias
* @info: passinfo struct
* Return: 1 on success, 0 on error
*/

int change_alias(passinfo_t *info)
{
	int i = 0;

list_t *temp;
char *alias;

for (i = 0; i < 10; i++)
{
temp = node_starts_with(info->alias, info->argv[0], '=');
if (!temp)
{
return (0);
}
free(info->argv[0]);
alias = _strchr(temp->str, '=');
if (!alias)
{
return (0);
}
alias = _strdup(alias + 1);
if (!alias)
{
return (0);
}
info->argv[0] = alias;
}
return (1);
}
