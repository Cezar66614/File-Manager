#include "node.h"

#include <stdlib.h>

void node_init(node_t *n)
{
    n->data = NULL;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->child = NULL;
}
