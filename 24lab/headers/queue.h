#ifndef _QUEUE_H
#define _QUEUE_H

#include "token.h"

struct q_item {
    token data;
    struct q_item* next;
};

typedef struct {
    struct q_item* first;
    struct q_item* last;
    int size;
} queue;

bool    queue_create(queue* q);
bool    queue_is_empty(queue *q);
int     queue_size(queue* q);
bool    queue_push(queue* q, token t);
token   queue_pop(queue* q);
void    queue_destroy(queue* q);
void    queue_clear(queue* q);

#endif
