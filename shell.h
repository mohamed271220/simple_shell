#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>


#define READ_BUFFER 1024
#define WRITE_BUFFER 1024
#define MAX_ARGS 64

#define BUFFER_FLUSH -1

#define CMD_NORMAL 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_PIPE 3

#define CONVER_TO_LOWER 1
#define CONVER_TO_UPPER 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".shell_history"
#define HISTORY_SIZE 4096

extern char *history[HISTORY_SIZE];

extern char **environ;

/**
* struct liststr - singly linked list for strings
* @str: string
* @next: points to the next node
* @num: number of nodes
*/
typedef struct liststr
{
	char *str;
	struct liststr *next;
	int num;

} list_t;

/**
* struct passinfo - struct to pass information to the functions
* @arg: argument
* @argv: argument vector
* @argc: argument count
* @env: environment
* @environ: environment
* @env_changed: environment changed
* @alias: alias
* @status: status
* @cmd: command
* @cmdtype: command type
* @line: line
* @line_flag: line flag
* @history: history
* @history_count: history count
* @file_name: file name
* @path: path
* @error: error
* @read_fd: read file descriptor
*/

typedef struct passinfo
{
	char *arg;

	char **argv;

	int argc;

	list_t *env;

	char **environ;

	int env_changed;

	list_t *alias;

	int status;

	char **cmd;

	int cmdtype;

	unsigned int line;

	int line_flag;

	list_t *history;

	int history_count;

	char *file_name;

	char *path;

	int error;

	int read_fd;

} passinfo_t;

#define PASSINFO_INIT {NULL, NULL, 0, NULL, NULL, 0, \
NULL, 0, NULL, 0, 0, 0, NULL, 0, NULL, NULL, 0, 0}

/**
* struct builtins - struct for builtins
* @name: name of the builtin
* @func: function pointer
*/

typedef struct builtins
{
	char *name;

	int (*func)(passinfo_t *);

} builtins_t;

/* _putchar */
void _puts(char *str);
void _putchar(char c);

/* string handlers */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);

/* string handlers 2 */
char *starts_with(char *s, char *start);
char *_strchr(char *s, char c);
char *_strncopy(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);
char **_strtow(char *str, char delim);

/* memory */
char *_memset(char *s, char b, unsigned int n);
void *_memcpy(void *dest, const void *src, unsigned int n);
void _free(char **ptr);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _free2(char **ptr);

/* utils */
int is_sh_mode(passinfo_t *info);
int is_delim(char c, char *delim);
int _isAlpha(char c);
int _atoi(char *s);
int _erratoi(char *s);

/* utils 2 */
void print_error(passinfo_t *info, char *msg);
int print_decimal(int n, int fd);
char *number_conversion(long int num, int base, int flag);
void remove_comments(char *str);

/* list handlers */
list_t *add_node(list_t **head, char *str, int num);
void free_list(list_t **head);
size_t print_list_s(list_t *head);
size_t list_len(list_t *head);
list_t *add_node_end(list_t **head, char *str, int num);

/* list handlers 2 */
size_t print_list(list_t *head);
list_t *node_starts_with(list_t *head, char *start, char c);
char **list_to_array(list_t *head);
size_t node_by_index(list_t *head, list_t *target);
int delete_node_at_index(list_t **head, unsigned int index);

/* error handlers */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(int fd, char c);
int _putsfd(int fd, char *str);



#endif
