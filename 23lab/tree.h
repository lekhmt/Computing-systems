#ifndef _TREE_H
#define _TREE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct node node;
typedef node* tree;

struct node{
    double val;
    tree left;
    tree right;
};

tree build_tree(tree left, double val, tree right);
bool tree_is_empty(tree t);
double get_root(tree t);
tree get_left(tree t);
tree get_right(tree t);
void destroy(tree t);

#endif