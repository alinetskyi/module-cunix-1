#include <stdlib.h>

typedef struct  node {
    void        *data;
    struct node *next;
}              node_t; 

node_t  *list_create(void *data) {
    node_t *head = malloc(sizeof(*node_t));
    node_t->data = data;
    node_t->next = NULL;
    return head
}

void list_destroy(node_t **head)
