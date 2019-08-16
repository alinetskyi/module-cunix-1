#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct  node {
    void        *data;
    char        *key;
    struct node *next;
}              node_t;

typedef struct  hashtable {
  unsigned int  size;
  void          **table;
}              hashtable_t;

node_t  *list_create(void *data, char *key) 
{
  node_t *head = malloc(sizeof(node_t));
  head->data = data;
  head->key = key;
  head->next = NULL;
  return head;
}

void    list_destroy(node_t **head)
{
  node_t *node = *head;
  node_t *next = node;
  void *data;
  while (node != NULL) 
  {
    next = node->next;
    data = node->data;
    free(node);
    node = next;
  }
}

void    list_push(node_t *head, void *data,char *key) 
{
  node_t *node = head;
  while (1) 
  {
    if (strcmp(node->key,key) == 0) 
    { 
        node->data = data;
	return;
    }	    
    if (node->next == NULL) {
	  node->next = malloc(sizeof(node_t));
	  break;	    
	}
	node = node->next;
  }
  node = node->next;
  node->data = data;
  node->key = key;
  node->next = NULL; 
}

void print_list(node_t *node)  
{
    while (node!=NULL) 
    {
        printf("%s : %s\n",node->key, (char*)(node->data));
	node = node->next;
    }
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
  ht->table = malloc(size*sizeof(void*));
  for (unsigned int i = 0; i <size; i++) 
  {
    (ht->table)[i] = NULL;
  }
  return ht;
}

void hash_destroy(hashtable_t *ht) 
{
  void **table = ht->table;
  unsigned int i;
  node_t *head;
  for (i = 0; i < ht->size; i++) 
  { 
    head = table[i];
    if (head != NULL) 
    {    
      list_destroy(&head);
    }
  }
  free(table);
  free(ht);
}

void hash_set(hashtable_t *ht, char *key, void *ptr) 
{
   unsigned int index = hash_func(key) % ht->size;
   void *pos = (ht->table)[index];
   if (pos == NULL) {
     (ht->table)[index] = list_create(ptr,key);
   } else {
      list_push((ht->table)[index], ptr, key);  
   }
}

void *hash_get(hashtable_t *ht, char *key) 
{
  unsigned int index = hash_func(key) % ht->size;
  void **table = ht->table;
  node_t *head = table[index];
  if (head == NULL) {
      return NULL;
  }
  while (strcmp(head->key,key) != 0) 
  {
    head=head->next;
  }
  if (head != NULL) 
  {
  return head->data;
  } else
  {
    return NULL;
  }
}

void print_table(hashtable_t *ht)
{
    void **table = ht->table;
    for (int i = 0; i < ht->size; i++) 
    {
        print_list(table[i]);
    }
}

/*
int main() {
    hashtable_t *ht =hash_create(10);
    hash_set(ht,"a","123");
    hash_set(ht,"a","123");  
    hash_set(ht,"a","123");
    printf("%s",hash_get(ht,"a"));
}
*/
