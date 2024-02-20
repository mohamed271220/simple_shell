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

    new_node = malloc(sizeof(list_t));
    if (new_node == NULL)
        return (NULL);
    new_node->str = _strdup(str);
    new_node->len = _strlen(str);
    new_node->num = num;
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
        if (head->str == NULL)
            _puts("(nil)\n");
        else
        {
            _puts(head->str);
            _putchar('\n');
        }
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
    list_t *new_node;
    list_t *last;

    new_node = malloc(sizeof(list_t));
    if (new_node == NULL)
        return (NULL);
    new_node->str = _strdup(str);
    new_node->len = _strlen(str);
    new_node->num = num;
    new_node->next = NULL;
    if (*head == NULL)
    {
        *head = new_node;
        return (new_node);
    }
    last = *head;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return (new_node);
}