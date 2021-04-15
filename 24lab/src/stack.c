#include "../headers/header.h"

typedef struct s_item item;

void s_create(stack* s){
    s->top = NULL;
    s->size = 0;
}

bool s_is_empty(stack* s){
    return s->size == 0;
}

int s_size(stack* s){
    return s->size;
}

bool s_push(stack* s, char c){
    item* i = malloc(sizeof(item));
    if (i == NULL){
        return false;
    } else {
        i->data = c;
        i->prev = s->top;
        s->top = i;
        s->size++;
        return true;
    }
}

char s_pop(stack* s){
    char c = s->top->data;
    item* i = s->top;
    s->top = s->top->prev;
    s->size--;
    free(i);
    return c;
}

void s_destroy(stack* s){
    while (s->top){
        s_pop(s);
    }
    s->top = NULL;
    s->size = 0;
}

void s_clear(stack* s){
    s_destroy(s);
    s_create(s);
}