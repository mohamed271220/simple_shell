#include "shell.h"

/**
* get_hf - gets the history file
* @info: passinfo struct
* Return: the history file
*/

char *get_hf(passinfo_t *info)
{
char *hf, *home;
home = get_env(info, "HOME=");
if (!home)
return (NULL);
hf = malloc(_strlen(home) + _strlen(HISTORY_FILE) + 1);
if (!hf)
return (NULL);
hf[0] = 0;
_strcpy(hf, home);
_strcat(hf, "/");
_strcat(hf, HISTORY_FILE);
return (hf);
}

/**
 * w_history - writes the history
 * @info: passinfo struct
 * Return: 1 on success, -1 on error
*/

int w_history(passinfo_t *info)
{
size_t fd;
char *file_name = get_hf(info);
list_t *history = NULL;
if (!file_name)
return (-1);
fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
free(file_name);
if (fd == -1)
return (-1);
for (history = info->history; history; history = history->next)
{
_putsfd(history->str, fd);
_putfd("\n", fd);
}
_putfd(BUFFER_FLUSH, fd);
close(fd);
return (1);
}

/**
 * r_history - reads the history
 * @info: passinfo struct
 * Return: count on success, 0 on error
*/

int r_history(passinfo_t *info)
{
int i, last = 0, count = 0;
size_t fd, read_len, fsize = 0;
strict stat st;
char *file_name = get_hf(info);
char *buffer = NULL;

if (!file_name)
return (0);
fd = open(file_name, O_RDONLY);
free(file_name);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buffer = malloc(fsize + 1);
if (!buffer)
return (0);
read_len = read(fd, buffer, fsize);
buffer[fsize] = 0;
if (read_len <= 0)
return (free(buffer), close(fd), 0);

for (i = 0; i < (int)fsize; i++)
if (buffer[i] == '\n')
{
buffer[i] = 0;
convert_to_list(info, buffer + last, count++);
last = i + 1;
}
if (last != i)
convert_to_list(info, buffer + last, count++);
free(buffer);
info->history_count = count;
while (info->history_count-- >= HISTORY_SIZE)
delete_node_at_index(&info->history, 0);
e_history(info)
return (info->history_count);
}

/**
 * convert_to_list - edits the history
 * @info: passinfo struct
 * @str: string to convert
 * @count: count
 * Return:  0
*/

int convert_to_list(passinfo_t *info, char *str, int count)
{
list_t *history = NULL;
if (!str)
return (0);
add_node_end(&info->history, str, count);
if (!info->history)
info->history = history;
return (0);
}

/**
 * e_history - edits the history
 * @info: passinfo struct
 * Return:  history count
*/

int e_history(passinfo_t *info)
{
list_t *history = info->history;
int i = 0;

while (history)
{
history->num = i++;
history = history->next;
}
return (info->history_count = i);
}
