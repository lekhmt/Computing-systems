#include "../headers/header.h"

#define item struct q_item

bool q_create(queue* q){
    item* new_elem = malloc(sizeof(item));
    if (new_elem == NULL){
        return false;
    } else {
        q->first = q->last = new_elem;
        q->size = 0;
        return true;
    }
}

bool q_is_empty(queue* q){
    return q->first == q->last;
}

int q_size(queue* q){
    return q->size;
}

bool q_push(queue* q, char c){
    item* tmp = malloc(sizeof(item));
    if (tmp == NULL){
        return false;
    } else {
        q->last->next = tmp;
        q->last->data = c;
        q->last = q->last->next;
        q->size++;
        return true;
    }
}

char q_pop(queue* q){
    char c = q->first->data;
    item* i = q->first;
    q->first = q->first->next;
    q->size--;
    free(i);
    return c;
}

void q_destroy(queue* q){
    item* next = q->first;
    while (next != q->last){
        item* tmp = next;
        next = next->next;
        free(tmp);
    }
    free(next);
}

void q_clear(queue* q){
    q_destroy(q);
    q_create(q);
}



