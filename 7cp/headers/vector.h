#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdbool.h>

typedef struct {
    int size;
    int capacity;
    double* buffer;
} vector;

void    create(vector* v);
void    destroy(vector* v);
bool    resize(vector* v, int new_size);
int     size(vector* v);
double  get(vector* v, int position);
void    set(vector* v, int position, double value);
bool    append(vector* v, double value);
void    clear(vector* v);

#endif
