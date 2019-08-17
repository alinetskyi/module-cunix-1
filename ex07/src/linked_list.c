#include <stdlib.h>
#include <stdio.h>
#include "../include/linked_list.h"

node_t  *list_create(void *data) 
{
  node_t *head = malloc(sizeof(node_t));
  head->data = data;
  head->next = NULL;
  return head;
}

void    list_destroy(node_t **head, void (*fp)(void *data)) 
{
  node_t *node = *head;
  node_t *next = node;
  void *data;
  while (node != NULL) 
  {
    next = node->next;
    data = node->data;
    fp(data);	 
    free(node);
    node = next;
  }
}

void    list_push(node_t *head, void *data) 
{
  node_t *node = head;
  while (1) {
    if (node->next == NULL) {
	  node->next = malloc(sizeof(node_t));
	  break;	    
	}
	node = node->next;
  }
  node = node->next;
  node->data = data;
  node->next = NULL; 
}

void    list_unshift(node_t **head, void *data) 
{
  node_t *new_head = malloc(sizeof(node_t));
  new_head->next = *head;
  new_head->data = data;
  *head = new_head;    
}

void    *list_pop(node_t **head) 
{
  node_t *node = *head;
  if (node == NULL) 
  {
  	return NULL;
  }
  while (node ->next->next !=  NULL)
  {
    node = node->next;
  }
  node_t *to_pop = node->next;
  void *data = to_pop->data;
  free(to_pop->data);
  free(to_pop);
  node->next = NULL;
  return data;
}
  
void    *list_shift(node_t **head) 
{
  if (*head == NULL) 
  { 
  	return NULL;
  }	
  node_t *temp = *head;
  void * data = temp->data;
  *head = (*head)->next;
  free(temp->data);
  free(temp);
  return data;
}

void    *list_remove(node_t **head, int pos) 
{
  node_t *node = *head;
  if (pos == 0) 
  { 
    return list_shift(head); 
  }
  int i,flag = 1;
  for (i = 0; i < pos - 1; i++) 
  {
    if (node == NULL) 
    {
	  flag = 0;
	  break;
	}
  node = node->next;
  }
  if (flag == 0) 
  { 
  	return *head; 
  }
  node_t *to_del = node->next;
  node->next = to_del->next;
  free(to_del->data);
  free(to_del);
  return *head;
}

void    list_print(node_t *head) 
{
  node_t *node = head;
  while (node != NULL) 
  {  
    printf("%p\n",node->data);
    node = node->next;
  }
}

void    list_visitor(node_t *head, void (*fp)(void *data)) 
{
  node_t *node = head;
  while (node != NULL) 
  {
    fp(node->data);
	node = node->next;
  } 
}