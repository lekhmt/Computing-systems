#ifndef _TOKEN_STACK_H
#define _TOKEN_STACK_H

struct token_s_item {
    token data;
    struct token_s_item* prev;
};

typedef struct {
    struct token_s_item* top;
    int size;
} token_stack;

void    token_stack_create(token_stack* s);
bool    token_stack_is_empty(token_stack* s);
int     token_stack_size(token_stack* s);
bool    token_stack_push(token_stack* s, token t);
token   token_stack_pop(token_stack* s);
void    token_stack_destroy(token_stack* s);
void    token_stack_clear(token_stack* s);

#endif