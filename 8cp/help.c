#include <stdbool.h>
#include <stdlib.h>

typedef struct list_element list_element;

struct list_element{
    double val;
    struct list_element* next;
};

typedef struct {
    struct list_element* first;
    struct list_element* last;
} list;

// функциональная спецификация списка
void    create(list* l);
void    destroy(list* l);

typedef struct {
    list_element* current;
} iterator;

double iterator_value(iterator it){
    return it.current->val;
}

iterator iterator_next(iterator it){
    it.current = it.current->next;
    return it;
}

bool iterator_equal(iterator it1, iterator it2){
    return it1.current == it2.current;
}

iterator begin(list* l){
    iterator it;
    it.current = l->first;
    return it;
}

iterator end(list* l){
    iterator it;
    it.current = NULL;
    return it;
}

void print(list* l){
    for (iterator it = begin(l); !iterator_equal(it, end(l)); it = iterator_next(it)){
        // печать
    }
}

