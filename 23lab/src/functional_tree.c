#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../headers/tree.h"

tree    create()            { return NULL; }
void    destroy(tree t)     { free(t); }
bool    is_empty(tree t)    { return t == NULL; }
Number  get_value(tree t)   { return t->value; }
tree    get_left(tree t)    { return t->left; }
tree    get_right(tree t)   { return t->right; }

tree build(tree left, Number value, tree right){
    tree tmp    = malloc(sizeof(node));
    tmp->left   = left;
    tmp->value  = value;
    tmp->right  = right;
    return tmp;
}

tree insert(tree t, Number value){
    if (is_empty(t)){
        return build(create(), value, create());
    } else if ( value < get_value(t) ){
        tree tmp = build(insert(get_left(t), value), get_value(t), get_right(t));
        destroy(t);
        return tmp;
    } else if ( value > get_value(t) ){
        tree tmp = build(get_left(t), get_value(t), insert(get_right(t), value));
        destroy(t);
        return tmp;
    } else {
        return t;
    }
}

void print(tree t, int h){
    if ( t != NULL ){
        print(t->right, h + 2);
        printf("|");
        for (int i = 0; i < h; ++i) { printf("-"); }
        printf("%s\n", get_enum_name(t->value));
        print(t->left, h + 2);
    }
}

tree remove_root(tree t, Number* new_value){
    if (!is_empty(get_left(t))){
        tree tmp = build(remove_root(get_left(t), new_value), get_value(t), get_right(t));
        destroy(t);
        return tmp;
    } else {
        *new_value = get_value(t);
        tree tmp = get_right(t);
        destroy(t);
        return tmp;
    }
}

tree delete(tree t, Number value){
    if (is_empty(t)){
        return t;
    } else if ( value < get_value(t) ){
        tree tmp = build(delete(get_left(t), value), get_value(t), get_right(t));
        destroy(t);
        return tmp;
    } else if ( value > get_value(t) ){
        tree tmp = build(get_left(t), get_value(t), delete(get_right(t), value));
        destroy(t);
        return tmp;
    } else {
        if (is_empty(get_right(t))){
            tree tmp = get_left(t);
            destroy(t);
            return tmp;
        } else if (is_empty(get_left(t))){
            tree tmp = get_right(t);
            destroy(t);
            return tmp;
        } else {
            Number new_value;
            tree new_right = remove_root(get_right(t), &new_value);
            tree tmp = build(get_left(t), new_value, new_right);
            destroy(t);
            return tmp;
        }
    }
}

void clear(tree t){
    if (is_empty(t)){
        return;
    }
    if (!is_empty(get_left(t))){
        clear(get_left(t));
    }
    if (!is_empty(get_right(t))){
        clear(get_right(t));
    }
    destroy(t);
}