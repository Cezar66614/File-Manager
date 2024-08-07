#include "node.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void node_init(node_t *n, void *data, uint64_t size) {
    if (size == 0) {
        n->data = data;
    } else {
        n->data = malloc(size);
        memcpy(n->data, data, size);
    }
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->child = NULL;
}
