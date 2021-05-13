#include "../headers/header.h"

typedef struct tree_s_item item;

void tree_stack_create(tree_stack* s){
    s->top = NULL;
    s->size = 0;
}

bool tree_stack_is_empty(tree_stack* s){
    return s->size == 0;
}

int tree_stack_size(tree_stack* s){
    return s->size;
}

bool tree_stack_push(tree_stack* s, tree t){
    item* i = malloc(sizeof(item));
    if (i == NULL){
        return false;
    } else {
        i->data = t;
        i->prev = s->top;
        s->top = i;
        s->size++;
        return true;
    }
}

tree tree_stack_pop(tree_stack* s){
    tree t = s->top->data;
    item* i = s->top;
    s->top = s->top->prev;
    s->size--;
    free(i);
    return t;
}

void tree_stack_destroy(tree_stack* s){
    while (s->top){
        tree_stack_pop(s);
    }
    s->top = NULL;
    s->size = 0;
}

void tree_stack_clear(tree_stack* s){
    tree_stack_destroy(s);
    tree_stack_create(s);
}