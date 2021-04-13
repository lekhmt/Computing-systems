#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "number.h"

typedef struct node node;
typedef node* tree;

struct node{
    Number value;
    tree left;
    tree right;
};

// функциональная спецификация бинарного дерева
tree    create();
void    destroy(tree t);
bool    is_empty(tree t);
Number  get_value(tree t);
tree    get_left(tree t);
tree    get_right(tree t);
tree    build(tree left, Number value, tree right);
tree    insert(tree t, Number value);
tree    delete(tree t, Number value);
void    print(tree t, int h);
void    clear(tree t);

#endif
