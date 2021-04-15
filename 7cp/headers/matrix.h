#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct {
    int m, n;
    vector values;
} matrix;

void    read_matrix(matrix* mtx);
void    print_vector(matrix* mtx);
void    print_matrix(matrix* mtz);
void    solve(double search, matrix* mtx);

#endif