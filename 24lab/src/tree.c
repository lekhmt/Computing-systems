#include "../headers/header.h"

tree    tree_create()            { return NULL; }
void    tree_destroy(tree t)     { free(t); }
bool    tree_is_empty(tree t)    { return t == NULL; }
token   tree_get_value(tree t)   { return t->value; }
tree    tree_get_left(tree t)    { return t->left; }
tree    tree_get_right(tree t)   { return t->right; }

tree tree_build(tree left, token value, tree right){
    tree tmp    = malloc(sizeof(node));
    tmp->left   = left;
    tmp->value  = value;
    tmp->right  = right;
    return tmp;
}

void tree_clear(tree t){
    if (tree_is_empty(t)){
        return;
    }
    if (!tree_is_empty(tree_get_left(t))){
        tree_clear(tree_get_left(t));
    }
    if (!tree_is_empty(tree_get_right(t))){
        tree_clear(tree_get_right(t));
    }
    tree_destroy(t);
}

void tree_print(tree t, int h){
    if (!is_empty(get_right(t))){
        tree_print(get_right(t), h + 2);
    }
    for (int i = 0; i < h; ++i){
        printf(".");
    }
    token tmp = get_value(t);
    if (tmp.type == CONST){
        printf("%lf\n", tmp.data.value);
    } else if (tmp.type == VARIABLE){
        printf("%s\n", tmp.data.name);
    } else {
        printf("%c\n", tmp.data.operator);
    }
    if (!is_empty(get_left(t))){
        tree_print(get_left(t), h + 2);
    }
}
