#include "../headers/header.h"

#define item struct q_item

bool queue_create(queue* q){
    item* new_elem = malloc(sizeof(item));
    if (new_elem == NULL){
        return false;
    } else {
        q->first = q->last = new_elem;
        q->size = 0;
        return true;
    }
}

bool queue_is_empty(queue* q){
    return q->first == q->last;
}

int queue_size(queue* q){
    return q->size;
}

bool queue_push(queue* q, token t){
    item* tmp = malloc(sizeof(item));
    if (tmp == NULL){
        return false;
    } else {
        q->last->next = tmp;
        q->last->data = t;
        q->last = q->last->next;
        q->size++;
        return true;
    }
}

token queue_pop(queue* q){
    token t = q->first->data;
    item* i = q->first;
    q->first = q->first->next;
    q->size--;
    free(i);
    return t;
}

void queue_destroy(queue* q){
    item* next = q->first;
    while (next != q->last){
        item* tmp = next;
        next = next->next;
        free(tmp);
    }
    free(next);
}

void queue_clear(queue* q){
    queue_destroy(q);
    queue_create(q);
}



