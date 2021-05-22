#ifndef _TREE_STACK_H
#define _TREE_STACK_H

#include "tree.h"

struct tree_s_item {
    tree data;
    struct tree_s_item* prev;
};

typedef struct {
    struct tree_s_item* top;
    int size;
} tree_stack;

void    tree_stack_create(tree_stack* s);
bool    tree_stack_is_empty(tree_stack* s);
int     tree_stack_size(tree_stack* s);
bool    tree_stack_push(tree_stack* s, tree t);
tree    tree_stack_pop(tree_stack* s);
void    tree_stack_destroy(tree_stack* s);
void    tree_stack_clear(tree_stack* s);
tree    tree_copy(tree t);

#endif