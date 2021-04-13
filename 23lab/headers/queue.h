#ifndef _QUEUE_H
#define _QUEUE_H

#include "tree.h"

struct item {
    tree data;
    struct item* next;
};

typedef struct {
    struct item* first;
    struct item* last;
    int size;
} queue;

bool    q_create(queue* q);
bool    q_is_empty(queue *q);
int     q_size(queue* q);
bool    q_push(queue* q, tree t);
tree    q_pop(queue* q);
void    q_destroy(queue* q);
void    q_clear(queue* q);

#endif
