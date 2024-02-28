#include "shell.h"

/**
* main - entry point
* @argc: argument count
* @argv: argument vector
* Return: 0 on success, 1 on error
*/

int main(int argc, char **argv)
{
passinfo_t passinfo[] = { PASSINFO_INIT };
int fd = 2;

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fd)
: "r" (fd)
);

if (argc == 2)
{
fd = open(argv[1], O_RDONLY);
if (fd == -1)
{
if (errno == EACCES)
{
exit(126);
}
if (errno == ENOENT)
{
_eputs(argv[0]);
_eputs(": 0: Can't open ");
_eputs(argv[1]);
_eputchar('\n');
_eputchar(BUFFER_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
passinfo->read_fd = fd;
}
populate_env(passinfo);
r_history(passinfo);
hsh(passinfo, argv);
return (EXIT_SUCCESS);
}
