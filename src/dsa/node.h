#pragma once
#include <stdint.h>

typedef struct node {
    void *data;
    struct node *left;    // generic data structures
    struct node *right;   // functionally next and prev
    struct node *parent;  // for trees
    struct node *child;   // for graphs
} node_t;

void node_init(node_t *n, void *data, uint64_t size);
