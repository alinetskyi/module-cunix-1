#include <stdlib.h>
#include "../include/binary_tree.h"

node_t *alloc_node() {
    node_t *node = malloc(sizeof(node_t));
    node->left = NULL;
    node->right = NULL;
    return node;
}

node_t *insert
