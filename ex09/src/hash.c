#include "../include/hash.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct  node {
    void        *data;
    struct node *next;
}              node_t;

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


unsigned int hash_func(char *key) 
{ 
  if (key == NULL)
  {
    return 0;
  }     	
  unsigned int index = 0;
  int i = 0;
  while (key[i] != '\0') 
  {
    index += (key[i] - '0');
    i++; 
  }
  return index;
}

hashtable_t *hash_create(unsigned int size) 
{ 
  if (size <= 0) 
  {
    return NULL; 	  
  }
  hashtable_t *ht = malloc(sizeof(hashtable_t));
  ht->size = size;
  ht->table = malloc(sizeof(void*));
  for (unsigned int i = 0; i <size; i++) 
  {
    (ht->table)[i] = NULL;
  }
  return ht;
}

void hash_destroy(hashtable_t *ht, void (*fp)(void *data)) 
{
  void **table = ht->table;
  for (unsigned int i = 0; i < ht->size; i++) 
  { 
    node_t *head = (node_t*)table[i];	  
    list_destroy(&head ,fp);
  }
  free(table);
}

void hash_set(hashtable_t *ht, char *key, void *ptr, void (*fp)(void *data)) 
{
   unsigned int index = hash_func(key) & ht->size;
   void *pos = (ht->table)[index];
   if (pos == NULL) {
     (ht->table)[index] = list_create(ptr);
   } else {
      list_push((ht->table)[index], ptr);  
   }
   fp(key);   
}

void *hash_get(hashtable_t *ht, char *key) 
{
  unsigned int index = hash_func(key) % ht->size;
  void **table = ht->table;
  node_t *head = table[index];
  if (head == NULL) {
      return NULL;
  }
  return head->data;
}	





int main() 
{
  hashtable_t *ht3 = hash_create(10000);
  return 0;
}
