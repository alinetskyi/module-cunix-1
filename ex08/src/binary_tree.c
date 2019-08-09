#include <stdlib.h>
#include "../include/binary_tree.h"
#include <stdio.h>

node_t *allocnode() {
    node_t *node = malloc(sizeof(node_t));
    node->left = NULL;
    node->right = NULL;
    node->key = 0;
    node->data = NULL;
    return node;
}

node_t *insert(node_t *root, char *key, void *data) {
    if (root == NULL) {
        return allocnode();
    }
    if (key <= root->key) {
        root->left = insert(root->left, key,data);
    } else {
        root->right = insert(root->right, key, data);
    }
    return root;
}

void print_node(node_t *node) {
    if (node != NULL) {	
        printf("%s : %p",node->key,node->data);
        print_node(node->left);
        print_node(node->right);
    }
}

void visit_tree(node_t *node, void (*fp)(node_t *root)) {
    if (node != NULL) {
        fp(node);
	fp(node->left);
	fp(node->right);
    }
}

void destroy_tree(node_t *node, void (*fdestroy)(node_t *root)) {
    if (node != NULL) {
        fdestroy(node->left);
	fdestroy(node->right);
	fdestroy(node);
    }
}
