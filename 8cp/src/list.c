#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "../headers/list.h"

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
    return (iterator){l, l->buffer[l->barrier_element].next_index};
}

iterator iter_end(list *l){
    return (iterator){l, l->barrier_element};
}

iterator iter_last_element(list *l){
    return iter_previous(iter_end(l));
}

void iter_insert_before(iterator *it, T val){
    it->list->size++;
    int insert_to = it->list->first_empty_index;
    it->list->first_empty_index = it->list->buffer[insert_to].next_index;
    it->list->buffer[insert_to].value = val;
    if(iter_is_equal(*it, iter_end(it->list))){
        it->list->buffer[insert_to].previous_index = it->list->barrier_element;
        it->list->buffer[insert_to].next_index = it->list->buffer[it->list->barrier_element].next_index;
        it->list->buffer[it->list->buffer[it->list->barrier_element].next_index].previous_index = insert_to;
        it->list->buffer[it->list->barrier_element].next_index = insert_to;
    } else{
        it->list->buffer[insert_to].previous_index = it->previous;
        it->list->buffer[insert_to].next_index = it->list->buffer[it->previous].next_index;
        it->list->buffer[it->list->buffer[it->previous].next_index].previous_index = insert_to;
        it->list->buffer[it->previous].next_index = insert_to;
    }
}

void iter_delete(iterator *it){
    if(!it->list->size){
        return;
    }
    it->list->size--;
    if(iter_is_equal(*it, iter_end(it->list))){
        int to_del = it->list->buffer[it->list->barrier_element].next_index;
        it->list->buffer[it->list->barrier_element].next_index = it->list->buffer[to_del].next_index;
        it->list->buffer[it->list->buffer[it->list->barrier_element].next_index].previous_index = it->list->barrier_element;
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
    l->barrier_element = 0;
    l->capacity = 10;
    l->buffer = malloc(l->capacity * sizeof(list_element));
    l->buffer[l->barrier_element].previous_index = l->barrier_element;
    l->buffer[l->barrier_element].next_index = l->barrier_element;
    for(int i = 1; i < l->capacity - 1; i++){
        l->buffer[i].next_index = i + 1;
    }
    l->buffer[l->capacity - 1].next_index = l->barrier_element;
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
    int cur_idx = l->buffer[l->barrier_element].next_index;
    while (i > 0){
        cur_idx = l->buffer[cur_idx].next_index;
        --i;
    }
    return l->buffer[cur_idx].value;
}

void list_print(list* l){
    for (iterator it = iter_begin(l); !iter_is_equal(it, iter_end(l)); it = iter_next(it)){
        printf("%d ", iter_get_value(it));
    }
    printf("\n");
}

int list_size(list* l){
    return l->size;
}

bool list_grow_buffer(list *l){
    int new_capacity = l->capacity * 3 / 2;
    if (new_capacity < 10){
        new_capacity = 10;
    }
    list_element* tmp = realloc(l->buffer, new_capacity * sizeof(list_element));
    if(tmp == NULL){
        return false;
    }
    l->buffer = tmp;
    l->first_empty_index = l->capacity;
    for(int i = l->capacity; i < new_capacity - 1; i++){
        l->buffer[i].next_index = i + 1;
    }
    l->buffer[new_capacity - 1].next_index = l->barrier_element;
    l->capacity = new_capacity;
    return true;
}

void list_insert(list *l, int i, T val){
    if(l->size + 2 > l->capacity){
        if(!list_grow_buffer(l)){
            return;
        }
    }
    int cur_idx = l->barrier_element;
    while(i > 0){
        cur_idx = l->buffer[cur_idx].next_index;
        i--;
    }
    iterator it = (iterator){l, cur_idx};
    iter_insert_before(&it, val);
}

void list_delete(list *l, int i){
    int cur_idx = l->barrier_element;
    while(i > 0){
        cur_idx = l->buffer[cur_idx].next_index;
        i--;
    }
    iterator it = (iterator){l, cur_idx};
    iter_delete(&it);
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

bool list_sorted(list *l){
    if (list_size(l) <= 2){
        return true;
    }
    iterator left = iter_begin(l);
    iterator right = iter_next(left);
    while (iter_get_value(left) == iter_get_value(right)){
        right = iter_next(right);
        if (iter_is_equal(right, iter_end(l))){
            return true;
        }
    }
    bool increase;
    if (iter_get_value(left) < iter_get_value(right)){
        increase = true;
    } else {
        increase = false;
    }
    left = right;
    right = iter_next(right);
    while (!iter_is_equal(right, iter_end(l))){
        if (iter_get_value(left) < iter_get_value(right)){
            if (!increase){
                return false;
            }
        } else if (iter_get_value(left) > iter_get_value(right)){
            if (increase){
                return false;
            }
        }
        left = right;
        right = iter_next(right);
    }
    return true;
}