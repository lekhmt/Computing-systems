#include "../headers/vector.h"
#include <stdlib.h>
#include <stdbool.h>

void create(vector* v){
    v->size     = 0;
    v->capacity = 0;
    v->buffer   = NULL;
}

void destroy(vector* v){
    v->size     = 0;
    v->capacity = 0;
    free(v->buffer);
    v->buffer   = NULL;
}

int size(vector* v){
    return v->size;
}

double get(vector* v, int position){
    return v->buffer[position];
}

void set(vector* v, int position, double value){
    v->buffer[position] = value;
}

bool grow_buffer(vector* v){
    int new_capacity = v->capacity * 3 / 2;
    if (v->capacity == 0){
        new_capacity = 10;
    }
    double* tmp = realloc(v->buffer, sizeof(double) * new_capacity);
    if (tmp != NULL){
        v->buffer = tmp;
        v->capacity = new_capacity;
        return true;
    } else {
        return false;
    }
}

bool append(vector* v, double value){
    if (v->size >= v->capacity){
        if (!grow_buffer(v)){
            return false;
        }
    }
    v->buffer[v->size] = value;
    v->size++;
    return true;
}

bool resize(vector* v, int new_size){
    if (v->capacity < new_size){
        double* tmp = realloc(v->buffer, sizeof(double) * new_size);
        if (tmp == NULL){
            return false;
        }
        v->buffer = tmp;
        v->capacity = new_size;
    }
    int first_size = v->size;
    v->size = new_size;
    for (int i = first_size; i < new_size; ++i){
        v->buffer[i] = 0;
    }
    return true;
}

void clear(vector* v){
    double* old = v->buffer;
    free(old);
    v->size = v->capacity = 0;
    v->buffer = NULL;
}
