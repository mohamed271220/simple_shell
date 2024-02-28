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
	ssize_t bytes = 0;
	size_t i = 0;

	if (!*size)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, signalHandler);
		#if USE_GETLINE
		bytes = getline(buffer, &i, stdin);
		#else
		bytes = _getline(info, buffer, &i);
		#endif
		if (bytes > 0 && *buffer)
		{
			if ((*buffer)[bytes - 1] == '\n')
			{
				(*buffer)[bytes - 1] = '\0';
				bytes--;
			}
			info->line_flag = 1;
			remove_comments(*buffer);
			convert_to_list(info, *buffer, info->history_count++);
			if (_strchr(*buffer, '\n'))
			{
				*size = bytes;
				info->cmd = buffer;
			}
		}
	}
	return (bytes);
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
	static char *buffer;

	static size_t i, j, len;
	ssize_t bytes = 0;
	char **buf_ptr = &(info->arg), *ptr;

	_putchar(BUFFER_FLUSH);
	bytes = input_buffer(info, &buffer, &len);
	if (bytes == -1)
		return (-1);
	if (len)
	{
		j = i;
		ptr = buffer + i;
		exec_chained(info, buffer, &j, i, len);
		while (j < len)
		{
			if (is_chained(info, buffer, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmdtype = CMD_NORMAL;
		}
		*buf_ptr = ptr;
		printf("info->arg:(iipu) %s\n", info->arg);
		return (_strlen(ptr));
	}
	*buf_ptr = buffer;
	printf("info->arg:(iin) %s\n", info->arg);
	return (bytes);
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
		return (-1);

	c = _strchr(buffer + i, '\n');
	j = c ? 1 + (unsigned int)(c - buffer) : l;

	new_ptr = _realloc(tmp, bytes, bytes ? bytes + j : j + 1);
	if (!new_ptr)
		return (-1);

	if (bytes)
		_strncat(new_ptr, buffer + i, j - i);
	else
		_strncpy(new_ptr, buffer + i, j - i + 1);
	bytes += j - i;
	i = j;
	tmp = new_ptr;
	if (len)
		*len = 0;
	*ptr = tmp;
	return (bytes);
}
