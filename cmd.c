#include "shell.h"

/**
* is_executable - if file is exe
* @info: info
* @path: path
* Return: 1 on success , 0 otherwise
*/

int is_executable(passinfo_t *info, char *path)
{
struct stat s;
(void)info;
if (!path || stat(path, &s))
return (0);
if (s.st_mode & S_IFREG)
return (1);
return (0);
}

/**
* mul_path - multiple path
* @path: path
* @start: start
* @end: end
* Return: pointer to the new path
*/

char *mul_path(char *path, int start, int end)
{
static char new_path[1024];
int i = 0;
int k = 0;
for (k = 0, i = start; i < end; i++)
if (path[i] != ':')
new_path[k++] = path[i];
new_path[k] = 0;
return (new_path);
}

/**
* find_path - find path
* @info: info
* @path: path
* @cmd: cmd
* Return: pointer to the new path or NULL
*/

char *find_path(passinfo_t *info, char *path, char *cmd)
{
int i = 0, j = 0;

char *new_path;

if (!path)
return (NULL);

if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_executable(info, cmd))
return (cmd);
}

while (1)
{
if (path[i] == ':' || !path[i])
{
new_path = mul_path(path, j, i);
if (!*new_path)
_strcat(new_path, cmd);
else
{
_strcat(new_path, "/");
_strcat(new_path, cmd);
}

if (is_executable(info, new_path))
return (new_path);
if (!path[i])
break;
j = i;
}
i++;
}
return (NULL);
}
