#include "shell.h"


/**
* input_buffer - reads the input buffer
* @info: info
* @buffer: address buffer
* @size: address size
* Return: bytes read
*/

ssize_t input_buffer(passinfo_t *info, char **buffer, size_t *size)
{
ssize_t r = 0;
	size_t len_p = 0;

	if (!*size)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, signalHandler);
#if USE_GETLINE
		r = getline(buffer, &len_p, stdin);
#else
		r = _getline(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->line_flag = 1;
			remove_comments(*buffer);
			convert_to_list(info, *buffer, info->history_count++);
			{
				*size = r;
				info->cmd = buffer;
			}
		}
	}
	return (r);
}


/**
* signalHandler - handles the signal
* @sig: signal
* Return: void
*/

void signalHandler(__attribute__((unused)) int sig)
{
_putchar('\n');
_putchar('$');
_putchar(' ');
_putchar(BUFFER_FLUSH);
}

/**
* get_input - gets the input
* @info: info
* Return: bytes read
*/

ssize_t get_input(passinfo_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUFFER_FLUSH);
	r = input_buffer(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		exec_chained(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chained(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd = CMD_NORMAL;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}


/**
* read_buffer - reads the buffer
* @info: info
* @buffer: address buffer
* @size: address size
* Return: bytes read
*/

ssize_t read_buffer(passinfo_t *info, char *buffer, size_t *size)
{
ssize_t bytes = 0;

if (*size)
return (0);
bytes = read(info->read_fd, buffer, READ_BUFFER);
if (bytes >= 0)
{
*size = bytes;
}
return (bytes);
}

/**
* _getline - gets the input
* @info: info
* @ptr: address ptr
* @len: length
* Return: bytes read
*/

int _getline(passinfo_t *info, char **ptr, size_t *len)
{
	static char buffer[READ_BUFFER];
	static size_t i, l;
	size_t j = 0;
	ssize_t bytes = 0, read = 0;
	char *tmp = NULL, *new_ptr = NULL, *c;

	tmp = *ptr;
	if (tmp && len)
		bytes = *len;
	if (i == l)
		i = l = 0;
	read = read_buffer(info, buffer, &l);
	if (read == -1 || (read == 0 && l == 0))
	{
		if (tmp)
			free(tmp);
		return (-1);
	}
	c = _strchr(buffer + i, '\n');
	j = c ? 1 + (unsigned int)(c - buffer) : l;

	new_ptr = _realloc(tmp, bytes, bytes ? bytes + j : j + 1);
	if (!new_ptr)
	{
		if (tmp)
			free(tmp);
		return (-1);
	}
	if (bytes)
		_strncat(new_ptr, buffer + i, j - i);
	else
		_strncpy(new_ptr, buffer + i, j - i + 1);
	bytes += j - i;
	i = j;
	tmp = new_ptr;
	if (len)
		*len = bytes;
	*ptr = tmp;
	return (bytes);
}
