#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "../headers/list.h"

int barrier_element = 0;

// iterator
T iter_get_value(iterator it){
    return it.list->buffer[it.previous].value;
}

void iter_set_value(iterator* it, T value){
    it->list->buffer[it->previous].value = value;
}

iterator iter_next(iterator it){
    return (iterator){it.list, it.list->buffer[it.previous].next_index};
}

iterator iter_previous(iterator it){
    return (iterator){it.list, it.list->buffer[it.previous].previous_index};
}

bool iter_is_equal(iterator it1, iterator it2){
    return it1.previous == it2.previous && it1.list == it2.list;
}

iterator iter_begin(list *l){
    return (iterator){l, l->buffer[barrier_element].next_index};
}

iterator iter_end(list *l){
    return (iterator){l, barrier_element};
}

iterator iter_last_element(list *l){
    return iter_previous(iter_end(l));
}

list_element *link_end(list *l){
    return &l->buffer[barrier_element];
}

void iter_insert_before(iterator *it, T val){
    it->list->size++;
    int insert_to = it->list->first_empty_index;
    it->list->first_empty_index = it->list->buffer[insert_to].next_index;
    it->list->buffer[insert_to].value = val;
    if(iter_is_equal(*it, iter_end(it->list))){
        it->list->buffer[insert_to].previous_index = barrier_element;
        it->list->buffer[insert_to].next_index = it->list->buffer[barrier_element].next_index;
        it->list->buffer[it->list->buffer[barrier_element].next_index].previous_index = insert_to;
        it->list->buffer[barrier_element].next_index = insert_to;
    } else{
        it->list->buffer[insert_to].previous_index = it->previous;
        it->list->buffer[insert_to].next_index = it->list->buffer[it->previous].next_index;
        it->list->buffer[it->list->buffer[it->previous].next_index].previous_index = insert_to;
        it->list->buffer[it->previous].next_index = insert_to;
    }
}

void iter_remove(iterator *it){
    if(!it->list->size){
        return;
    }
    it->list->size--;
    if(iter_is_equal(*it, iter_end(it->list))){
        int to_del = it->list->buffer[barrier_element].next_index;
        it->list->buffer[barrier_element].next_index = it->list->buffer[to_del].next_index;
        it->list->buffer[it->list->buffer[barrier_element].next_index].previous_index = barrier_element;
        it->list->buffer[to_del].next_index = it->list->first_empty_index;
        it->list->first_empty_index = to_del;
    } else{
        int to_del = it->list->buffer[it->previous].next_index;
        it->list->buffer[it->list->buffer[to_del].previous_index].next_index = it->list->buffer[to_del].next_index;
        it->list->buffer[it->list->buffer[to_del].next_index].previous_index = it->list->buffer[to_del].previous_index;
        it->list->buffer[to_del].next_index = it->list->first_empty_index;
        it->list->first_empty_index = to_del;
    }
}

void list_create(list *l){
    l->capacity = 20;
    l->buffer = malloc(l->capacity * sizeof(list_element));
    l->buffer[barrier_element].previous_index = barrier_element;
    l->buffer[barrier_element].next_index = barrier_element;
    for(int i = 1; i < l->capacity - 1; i++){
        l->buffer[i].next_index = i + 1;
    }
    l->buffer[l->capacity - 1].next_index = barrier_element;
    l->first_empty_index = 1;
    l->size = 0;
}

void list_destroy(list *l){
    free(l->buffer);
    l->capacity = 0;
    l->first_empty_index = 1;
    l->size = 0;
}

bool list_is_empty(list* l){
    return l->size == 0;
}

T list_get(list* l, int i){
    int cur_idx = l->buffer[barrier_element].next_index;
    while (i > 0){
        cur_idx = l->buffer[cur_idx].next_index;
    }
    return l->buffer[cur_idx].value;
}

void list_print(list* l){
    for(iterator it = iter_begin(l); !iter_is_equal(it, iter_end(l)); it = iter_next(it)){
        printf("%d ", iter_get_value(it));
    }
    printf("\n");
}

int list_size(list* l){
    return l->size;
}

bool list_grow_buffer(list *l){
    int tmp = l->capacity * 3 / 2;
    list_element* newd = realloc(l->buffer, tmp * sizeof(list_element));
    if(newd == NULL){
        fprintf(stderr, "Not enough memory\n");
        return false;
    }
    l->buffer = newd;
    l->first_empty_index = l->capacity;
    for(int i = l->capacity; i < tmp - 1; i++){
        l->buffer[i].next_index = i + 1;
    }
    l->buffer[tmp - 1].next_index = barrier_element;
    l->capacity = tmp;
    return true;
}

void list_insert(list *l, int i, T val){
    if(l->size + 2 > l->capacity){
        if(!list_grow_buffer(l)){
            return;
        }
    }
    int cur_idx = barrier_element;
    while(i > 0){
        cur_idx = l->buffer[cur_idx].next_index;
        i--;
        if(cur_idx == barrier_element){
            fprintf(stderr, "Index out of bounds\n");
            return;
        }
    }
    iterator it = (iterator){l, cur_idx};
    iter_insert_before(&it, val);
}

void list_delete(list *l, int i){
    int cur_idx = barrier_element;
    if(i < 0){
        fprintf(stderr, "Index out of bounds\n");
        return;
    }
    while(i > 0){
        cur_idx = l->buffer[cur_idx].next_index;
        i--;
        if(cur_idx == barrier_element){
            fprintf(stderr, "Index out of bounds\n");
            return;
        }
    }
    iterator it = (iterator){l, cur_idx};
    iter_remove(&it);
}

void list_push_front(list *l, T val){
    list_insert(l, 0, val);
}

void list_push_back(list *l, T val){
    list_insert(l, list_size(l), val);
}

void list_pop_front(list *l){
    list_delete(l, 0);
}

void list_pop_back(list *l){
    list_delete(l, list_size(l) - 1);
}

void list_iter_swap(iterator* a, iterator* b){
    T t = iter_get_value(*b);
    iter_set_value(b, iter_get_value(*a));
    iter_set_value(a, t);
}

void list_reverse(list *l){
    iterator front = iter_begin(l);
    iterator back = iter_previous(iter_end(l));
    for(int i = 0; i < list_size(l) / 2; i++){
        list_iter_swap(&front, &back);
        front = iter_next(front);
        back = iter_previous(back);
    }
}