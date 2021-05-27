#ifndef _LIST_H
#define _LIST_H

typedef double T;

typedef struct {
    T value;
    int previous_index;
    int next_index;
} list_element;

typedef struct {
    list_element* buffer;
    int capacity;
    int size;
    int first_empty_index;
    int barrier_element;
} list;

typedef struct {
    list* list;
    int previous;
} iterator;


T        iter_get_value     (iterator it);
void     iter_set_value     (iterator* it, T value);
iterator iter_next          (iterator it);
iterator iter_previous      (iterator it);
bool     iter_is_equal      (iterator it1, iterator it2);
iterator iter_begin         (list* l);
iterator iter_end           (list* l);
iterator iter_last_element  (list* l);
void     iter_insert_before (iterator* it, T value);
void     iter_delete        (iterator* it);

void     list_create        (list* l);
void     list_destroy       (list* l);
bool     list_is_empty      (list* l);
T        list_get           (list* l, int index);
void     list_print         (list* l);
int      list_size          (list* l);
void     list_insert        (list* l, int index, T value);
void     list_push_front    (list* l, T value);
void     list_push_back     (list* l, T value);
void     list_pop_front     (list* l);
void     list_pop_back      (list* l);
void     list_delete        (list* l, int index);
bool     list_sorted       (list* l);

#endif