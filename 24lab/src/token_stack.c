#include "../headers/header.h"

typedef struct token_s_item item;

void token_stack_create(token_stack* s){
    s->top = NULL;
    s->size = 0;
}

bool token_stack_is_empty(token_stack* s){
    return s->size == 0;
}

int token_stack_size(token_stack* s){
    return s->size;
}

bool token_stack_push(token_stack* s, token t){
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

token token_stack_pop(token_stack* s){
    token t = s->top->data;
    item* i = s->top;
    s->top = s->top->prev;
    s->size--;
    free(i);
    return t;
}

void token_stack_destroy(token_stack* s){
    while (s->top){
        token_stack_pop(s);
    }
    s->top = NULL;
    s->size = 0;
}

void token_stack_clear(token_stack* s){
    token_stack_destroy(s);
    token_stack_create(s);
}