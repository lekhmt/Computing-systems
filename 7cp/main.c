// вариант представления 2: 1 вектор
// задание 3: найти элемент матрцы, ближайший к заданному значению и разделить на него элементы его строки и столбца

#include <stdio.h>
#include "headers/vector.h"
#include "headers/matrix.h"

int main(){

    matrix mtx;
    read_matrix(&mtx);
    print_vector(&mtx);
    printf("\n");
    print_matrix(&mtx);
    printf("\n");

    double elem;
    scanf("%lf", &elem);

    solve(elem, &mtx);

}