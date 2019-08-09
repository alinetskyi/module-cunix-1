#include "../include/linked_list.h"
#include <stdlib.h>
#include <stdio.h>

node_t      *list_create(void *data)
{
    node_t *list;

    list = (node_t *)malloc(sizeof(node_t));
    if (data != NULL)
        list->data = data;
    else
        list->data = NULL;
    list->next = NULL;
    return (list);
}

void        list_destroy(node_t **head, void (*fp)(void *data))
{
    node_t  *tmp;
    node_t  *new;

    if (*head == NULL || fp == NULL)
        return ;
    tmp = *head;
    while (tmp != NULL)
    {
        fp(tmp->data);
        new = tmp->next;
        free(tmp);
        tmp = new;
    }
    *head = NULL;
}

void    list_push(node_t *head, void *data)
{
    node_t  *tmp;

    if (head == NULL)
        return ;
    tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = (node_t *)malloc(sizeof(node_t));
    tmp->next->data = data;
    tmp->next->next = NULL;
}

void    list_unshift(node_t **head, void *data)
{
    node_t *tmp;

    if (!(tmp = (node_t *)malloc(sizeof(node_t))))
        return ;
    if (data != NULL)
        tmp->data = data;
    else
        tmp->data = NULL;
    tmp->next = *head;
    *head = tmp;
}

void    *list_pop(node_t **head)
{
    node_t *tmp;

    if (*head == NULL)
        return ((void *)-1);
    if ((*head)->next == NULL)
    {
        free(head);
        return (NULL);
    }
    tmp = *head;
    while (tmp->next->next)
        tmp = tmp->next;
    free(tmp->next);
    tmp->next = NULL;
    return(*head);
}

void    *list_shift(node_t **head)
{
    node_t *tmp;

    tmp = *head;
    *head = (*head)->next;
    free(tmp->data);
    free(tmp);
    
    return (*head);
}

void    *list_remove(node_t **head, int pos)
{
    node_t *tmp;
    node_t *delete;
    int     i;

    i = 0;
    if (*head == NULL || pos == 0)
        return ((void *)-1);
    tmp = *head;
    while (i < (pos - 1))
    {
        if (tmp->next == NULL)
            return ((void *)-1);
        tmp = tmp->next;
        i++;
    }
    delete = tmp->next;
    tmp->next = delete->next;
    free(delete);
    return (*head);
}

void    list_print(node_t *head)
{
        node_t *tmp;
        
        if (head == NULL)
            return ;
        tmp = head;
        while (tmp != NULL)
        {
            if (tmp->data != NULL)
                printf("%s\n", (char *)tmp->data);
            tmp = tmp->next;
        }
}

void    list_visitor(node_t *head, void (*fp)(void *data))
{
    node_t *tmp;

	if (head == NULL || fp == NULL)
	    return ;
    tmp = head;
	while (tmp->next)
	{
        if (tmp->data == NULL)
            return;
		fp(tmp->data);
    }
}

