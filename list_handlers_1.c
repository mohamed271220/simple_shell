#include "shell.h"

/**
* add_node - adds a new node at the beginning of a list_t list
* @head: pointer to the head of the list
* @str: string to be added to the list
* @num: number to be added to the list

* Return: address of the new element, or NULL if it failed
*/

list_t *add_node(list_t **head, char *str, int num)
{
list_t *new_node;
if (head == NULL)
return (NULL);
new_node = malloc(sizeof(list_t));
if (new_node == NULL)
return (NULL);
_memset((void *)new_node, 0, sizeof(list_t));
new_node->num = num;
if (str)
{
new_node->str = _strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
new_node->next = *head;
*head = new_node;
return (new_node);
}

/**
* free_list - frees a list_t list
* @head: pointer to the head of the list
* Return: void
*/

void free_list(list_t **head)
{
list_t *current;
list_t *next;

current = *head;
while (current != NULL)
{
next = current->next;
free(current->str);
free(current);
current = next;
}
*head = NULL;
}

/**
* print_list_s - prints all the elements of a list_t list
* @head: pointer to the head of the list
* Return: the number of nodes
*/

size_t print_list_s(list_t *head)
{
size_t count;

count = 0;
while (head != NULL)
{
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
count++;
}
return (count);
}

/**
* list_len - returns the number of elements in a linked list_t list
* @head: pointer to the head of the list
* Return: the number of nodes
*/

size_t list_len(list_t *head)
{
size_t count;

count = 0;
while (head != NULL)
{
head = head->next;
count++;
}
return (count);
}

/**
* add_node_end - adds a new node at the end of a list_t list
* @head: pointer to the head of the list
* @str: string to be added to the list
* @num: number to be added to the list
* Return: address of the new element, or NULL if it failed
*/


list_t *add_node_end(list_t **head, char *str, int num)
{
list_t *new_node, *node;

if (!head)
return (NULL);

node = *head;
new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);
_memset((void *)new_node, 0, sizeof(list_t));
new_node->num = num;
if (str)
{
new_node->str = _strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;
return (new_node);
}
