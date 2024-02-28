#include "shell.h"


/**
* get_environ - gets the environment
* @info: passinfo struct
* Return: 0
*/

char **get_environ(passinfo_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_array(info->env);
info->env_changed = 0;
}
return (info->environ);
}


/**
* _remove_env - removes the environment
* @info: passinfo struct
* @name: name of the environment variable
* Return: 1 on success, 0 on error
*/

int _remove_env(passinfo_t *info, char *name)
{
list_t *env = info->env;
size_t i = 0;
char *ptr;

if (!env || !name)
{
return (0);
}

while (env)
{
ptr = starts_with(env->str, name);
if (ptr && *ptr == '=')
{
info->env_changed = delete_node_at_index(&(info->env), i);
i = 0;
env = info->env;
continue;
}
env = env->next;
i++;
}
return (info->env_changed);
}

/**
* _set_env - sets the environment
* @info: passinfo struct
* @name: name of the environment variable
* @value: value of the environment variable
* Return:  0
*/

int _set_env(passinfo_t *info, char *name, char *value)
{
char *buffer = NULL;
list_t *env;
char *ptr;

if (!name || !value)
{
return (0);
}
buffer = malloc(_strlen(name) + _strlen(value) + 2);
if (!buffer)
{
return (0);
}
_strcpy(buffer, name);
_strcat(buffer, "=");
_strcat(buffer, value);
env = info->env;
while (env)
{
ptr = starts_with(env->str, name);
if (ptr && *ptr == '=')
{
free(env->str);
env->str = buffer;
info->env_changed = 1;
return (0);
}
env = env->next;
}
add_node_end(&info->env, buffer, 0);
free(buffer);
info->env_changed = 1;
return (0);
}

/**
* set_env - sets the environment
* @info: passinfo struct
* Return: 0 on success, 1 on error
*/

int set_env(passinfo_t *info)
{
if (info->argc != 3)
{
_eputs("Invalid number of arguments\n");
return (1);
}
if (_set_env(info, info->argv[1], info->argv[2]))
{
return (0);
}
return (1);
}


/**
* remove_env - removes the environment
* @info: passinfo struct
* Return: 0 on success, 1 on error
*/

int remove_env(passinfo_t *info)
{
int i = 0;
if (info->argc == 1)
{
_eputs("Invalid number of arguments\n");
return (1);
}
for (i = 1; i < info->argc; i++)
_remove_env(info, info->argv[i]);
return (0);
}
