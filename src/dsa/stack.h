#pragma once
#include <stdint.h>

#include "node.h"

typedef struct stack {
    struct node head;
    struct node *tail;
    struct node *current;
    uint32_t length;
} stack_t;

void stack_init(stack_t *stk);
void stack_push(stack_t *stk, node_t *node);
node_t *stack_pop(stack_t *stk);
