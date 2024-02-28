#include "shell.h"

/**
* delete_node_at_index - deletes the node at index index of a listint_t list
* @head: pointer to the head of the list
* @index: index of the node that should be deleted
* Return: 1 if it succeeded, -1 if it failed
*/

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *current;
	list_t *next;
	unsigned int i;

	if (*head == NULL)
		return (-1);
	if (index == 0)
	{
		next = (*head)->next;
		free((*head)->str);
		free(*head);
		*head = next;
		return (1);
	}
	current = *head;
	for (i = 0; i < index - 1; i++)
	{
		if (current->next == NULL)
			return (-1);
		current = current->next;
	}
	next = current->next;
	current->next = next->next;
	free(next->str);
	free(next);
	return (1);
}

/**
* list_to_array - converts a list_t list to an array of strings
* @head: pointer to the head of the list
* Return: pointer to the resulting array
*/

char **list_to_array(list_t *head)
{
	char **array;

	list_t *current;
	int i;

	unsigned int len;

	if (head == NULL)
		return (NULL);
	current = head;
	for (len = 0; current != NULL; len++)
		current = current->next;
	array = malloc(sizeof(char *) * (len + 1));
	if (array == NULL)
		return (NULL);
	current = head;
	for (i = 0; i < (int)len; i++)
	{
		array[i] = _strdup(current->str);
		if (array[i] == NULL)
		{
			for (i--; i >= 0; i--)
				free(array[i]);
			free(array);
			return (NULL);
		}
		current = current->next;
	}
	array[i] = NULL;
	return (array);
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

	while (head != NULL)
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

size_t node_by_index(list_t *head, list_t *target)
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
