#ifndef _TREE_H
#define _TREE_H

typedef struct node node;
typedef node* tree;

struct node{
    token value;
    tree left;
    tree right;
};

// функциональная спецификация бинарного дерева
tree    tree_create();
void    tree_destroy(tree t);
bool    tree_is_empty(tree t);
token   tree_get_value(tree t);
tree    tree_get_left(tree t);
tree    tree_get_right(tree t);
tree    tree_build(tree left, token value, tree right);
void    tree_clear(tree t);
void    tree_print(tree t, int h);

#endif
