#include <stdlib.h>
#include "../include/binary_tree.h"
#include <stdio.h>
#include <string.h>


node_t *allocnode() 
{
  node_t *node = malloc(sizeof(node_t));
  node->left = NULL;
  node->right = NULL;
  node->key = NULL;
  node->data = NULL;
  return node;
}

node_t *insert(node_t *root, char *key, void *data) 
{
  if (root == NULL) 
  {
    node_t *new_node = allocnode();
    new_node->key = key;
    new_node->data = data;
    return new_node;
  }
  if (strcmp(root->key,key) >  0) 
  {
    root->left = insert(root->left, key,data);
  } else 
  {
    root->right = insert(root->right, key, data);
  }
  return root;
}

void print_node(node_t *node) 
{
  if (node != NULL) 
  {	
    printf("%s : %p\n",node->key,node->data);
    print_node(node->left);
    print_node(node->right);
  }
}

void visit_tree(node_t *node, void (*fp)(node_t *root)) 
{
  if (node != NULL) 
  {
    fp(node);
	visit_tree(node->left,fp);
	visit_tree(node->right,fp);
  }
}

void destroy_tree(node_t *node, void (*fdestroy)(node_t *root)) 
{
  if (node != NULL) 
  {
    destroy_tree(node->left,fdestroy);
	destroy_tree(node->right,fdestroy);
	fdestroy(node);
	free(node);
  }
}