#ifndef _TREE_H
#define _TREE_H

typedef struct node node;
typedef node* tree;

struct node{
    int value;
    tree left;
    tree right;
};

// функциональная спецификация бинарного дерева
tree    create();
void    destroy(tree t);
bool    is_empty(tree t);
int     get_value(tree t);
tree    get_left(tree t);
tree    get_right(tree t);
tree    build(tree left, int value, tree right);
tree    insert(tree t, int value);
tree    delete(tree t, int value);
void    print(tree t, int h);
void    clear(tree t);

#endif
