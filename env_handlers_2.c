#include "shell.h"

/**
* print_env - prints the environment
* @info: passinfo struct
* Return: 0
*/

int print_env(passinfo_t *info)
{
print_list_s(info->env);
return (0);
}

/**
* get_env - gets the environment
* @info: passinfo struct
* @name: name of the environment variable
* Return: the value
*/

char *get_env(passinfo_t *info, char *name)
{
list_t *env = info->env;
char *value;
while (env)
{
value = starts_with(env->str, name);
if (value && *value)
return (value);
env = env->next;
}
return (NULL);
}

/**
* populate_env - populates the environment
* @info: passinfo struct
* Return: 0 on success, 1 on error
*/

int populate_env(passinfo_t *info)
{
list_t *env = NULL;
size_t len;

for (len = 0; environ[len]; len++)
add_node_end(&env, environ[len], 0);

info->env = env;
return (0);
}
