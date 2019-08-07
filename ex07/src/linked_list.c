#include <stdlib.h>
#include <stdio.h>
#include "../include/linked_list.h"

typedef struct  node {
    void        *data;
    struct node *next;
}              node_t;

node_t  *list_create(void *data) {
    node_t *head = malloc(sizeof(node_t));
    head->data = data;
    head->next = NULL;
    return head;
}

void    list_destroy(node_t **head, void (*fp)(void *data)) {
    node_t *node = *head;
    node_t *next = node;
    void *data;
    while (node != NULL) {
         next = node->next;
         data = node->data;
         fp(data);	 
         free(node);
         node = next;
   }
}

void    list_push(node_t *head, void *data) {
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

void    list_unshift(node_t **head, void *data) {
    node_t *old_head = *head;
    node_t *new_head = malloc(sizeof(node_t));
    new_head->next = old_head;
    new_head->data = data;    
}

void    *list_pop(node_t **head) {
    node_t *node = *head;
    if (node == NULL) { return NULL;}
    while (node -> next != NULL){
       node = node->next;
    }
    void *data = node->next;
    free(node);
    return data;

void    *list_shift(node_t **head) {
    if (*head == NULL) { return NULL;}	
    node_t *new_head =(*head)->next;
    free(*head);
    return new_head;
}

void    *list_remove(node_t **head, int pos) {
    node_t *node = *head;
    int i;
    int flag = 1;
    for (i = 0; i < pos; i++) {
        if (node == NULL) {
	       	break;
                flag = 0;       
	}
	node = node->next;
    }
    if (flag) {
       node->next = node->next->next;
       free(node->next);  
    }  
    return NULL;
}

void    list_print(node_t *head) {
    node_t *node = head;
    while (node != NULL) {  
        printf("%p\n",node->data);
	node = node->next;
    }
}

void    list_visitor(node_t *head, void (*fp)(void *data)) {
    node_t*node = head;
    while (node != NULL) {
        fp(node->data);
	node= node->next;
    } 
}


/*
int main() {
    node_t *list = list_create("madagaskar");
    list_push(&list,"oslo");
    list_push(&list,"london");
    list_push(&list,"paris");
    list_push(&list,"kyiv");
    list_print(list);
}
*/ 
