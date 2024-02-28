#include "shell.h"

/**
* delete_node_at_index - deletes the node at index index of a listint_t list
* @head: pointer to the head of the list
* @index: index of the node that should be deleted
* Return: 1 if it succeeded, -1 if it failed
*/

int delete_node_at_index(list_t **head, unsigned int index)
{
list_t *node, *prev;
unsigned int i = 0;
if (!head || !*head)
return (0);
if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}
node = *head;
while (node)
{
if (i == index)
{
prev->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev = node;
node = node->next;
}
return (0);
}

/**
* list_to_array - converts a list_t list to an array of strings
* @head: pointer to the head of the list
* Return: pointer to the resulting array
*/

char **list_to_array(list_t *head)
{
list_t *node = head;
size_t i = list_len(head), j;
char **strs;
char *str;
if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
str = _strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}


/**
* print_list - prints all the elements of a list_t list
* @head: pointer to the head of the list
* Return: the number of nodes
*/

size_t print_list(list_t *head)
{
size_t count = 0;
while (head != NULL)
{
_puts(number_conversion(head->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
count++;
}
return (count);
}
/**
* node_starts_with - checks if a node starts with a given string
* @head: pointer to the node
* @start:  string to be checked
* @c: character to be checked
* Return: 1 if it starts with the string, 0 if it doesn't
*/

list_t *node_starts_with(list_t *head, char *start, char c)
{
char *ptr = NULL;

while (head)
{
ptr = starts_with(head->str, start);
if (ptr && (c == '\0' || *ptr == c))
return (head);
head = head->next;
}
return (NULL);
}

/**
* node_by_index - returns the node at index index of a list_t list
* @head: pointer to the head of the list
* @target: index of the node that should be returned
* Return: pointer to the node, or -1 if it failed
*/

ssize_t node_by_index(list_t *head, list_t *target)
{
size_t i = 0;
while (head)
{
if (head == target)
return (i);
head = head->next;
i++;
}
return (-1);
}
