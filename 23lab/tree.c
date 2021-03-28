#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

tree build_tree(tree left, double val, tree right){
    tree tmp = malloc(sizeof(node));
    tmp->left = left;
    tmp->val = val;
    tmp->right = right;
    return tmp;
}

bool tree_is_empty(tree t){
    return t == NULL;
}

double get_root(tree t){
    return t->val;
}

tree get_left(tree t){
    return t->left;
}

tree get_right(tree t){
    return t->right;
}

void destroy(tree t){
    // дописать
}
