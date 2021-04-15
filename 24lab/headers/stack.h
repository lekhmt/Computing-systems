#ifndef _STACK_H
#define _STACK_H

struct s_item {
    char data;
    struct s_item* prev;
};

typedef struct {
    struct s_item* top;
    int size;
} stack;

void    s_create(stack* s);
bool    s_is_empty(stack* s);
int     s_size(stack* s);
bool    s_push(stack* s, char c);
char    s_pop(stack* s);
void    s_destroy(stack* s);
void    s_clear(stack* s);

#endif