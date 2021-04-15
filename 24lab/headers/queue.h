#ifndef _QUEUE_H
#define _QUEUE_H

struct q_item {
    char data;
    struct q_item* next;
};

typedef struct {
    struct q_item* first;
    struct q_item* last;
    int size;
} queue;

bool    q_create(queue* q);
bool    q_is_empty(queue *q);
int     q_size(queue* q);
bool    q_push(queue* q, char c);
char    q_pop(queue* q);
void    q_destroy(queue* q);
void    q_clear(queue* q);

#endif
