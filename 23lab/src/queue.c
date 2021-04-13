#include <stdlib.h>
#include <stdbool.h>
#include "../headers/queue.h"

#define item struct item

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

bool q_push(queue* q, tree t){
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

tree q_pop(queue* q){
    if (q->first != q->last){
        tree t = q->first->data;
        item* i = q->first;
        q->first = q->first->next;
        q->size--;
        free(i);
        return t;
    }
    return NULL;
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



