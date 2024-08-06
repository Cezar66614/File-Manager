#include "stack.h"

#include "node.h"

void stack_init(stack_t *stk)
{
    node_init(&stk->head);
    stk->tail = &stk->head;
    stk->length = 0;
}

void stack_push(stack_t *stk, node_t *node)
{
    if (stk->length++ == 0)
    {
        stk->head = *node;
        stk->tail = &stk->head;
        return;
    }
    node->parent = stk->tail;
    stk->tail->child = node;
    stk->tail = stk->tail->child;
}

node_t *stack_pop(stack_t *stk)
{
    // according to a keynote on c it is bad to use allocators in library code
    // LINK: https://youtu.be/QpAhX-gsHMs?t=2290
    stk->tail = stk->tail->parent;
    return stk->tail->child;
}
