#include "../include/hash.h"
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char *key;
  void *data;
  struct node *next;
} node_t;

node_t  *list_create(void *data, char *key) 
{
  node_t *head = malloc(sizeof(node_t));
  head->data = data;
  head->next = NULL;
  head->key = key;
  return head;
}

unsigned int hash_func(char *key) 
{
  unsigned int index = 0;
  int i = 0;
  while (key[i] != '\0') 
  {
    index += (key[i] - '0');
    i++; 
  }
  return index;
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
    free(data);
    free(node->key);    
    free(node);
    node = next;
  }
}

void    list_push(node_t *head, void *data, char *key) 
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
  node->key = key;
}

hashtable_t *hash_create(unsigned int size) 
{
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
     (ht->table)[index] = list_create(ptr,key);
   } else {
      list_push((ht->table)[index], ptr, key);  
   }
   fp(key);   
}

void *hash_get(hashtable_t *ht, char *key) 
{
  unsigned int index = hash_func(key) % ht->size;
  void **table = ht->table;
  node_t *head = table[index];
  while (head != NULL) 
  {
    if (strcmp(head->key,key) == 0) 
    {
      return head->data;
    }
    head = head->next;
  }
  return NULL; 
}	





//int main() 
//{i
//  return 0;
///}
