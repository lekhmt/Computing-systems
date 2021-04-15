#include <stdio.h>
#include <float.h>
#include <math.h>
#include "../headers/vector.h"
#include "../headers/matrix.h"


void print_zeroes(int n){
    for (int i = 0; i < n; ++i){
        printf("0.0 ");
    }
}

void read_matrix(matrix* mtx){

    int m, n;
    vector* v = &mtx->values;
    create(v);
    scanf("%d %d", &m, &n);

    mtx->m = m;
    mtx->n = n;

    for (int i = 0; i < m; ++i){
        bool appended = false;
        for (int j = 0; j < n; ++j){
            double elem;
            scanf("%lf", &elem);
            if (elem != 0){
                if (!appended){
                    append(v, -1);
                    append(v, i);
                    appended = true;
                }
                append(v, j);
                append(v, elem);
            }
        }
    }
    append(v, -1);
    append(v, -1);
}

void print_matrix(matrix* mtx){

    int m = mtx->m;
    int n = mtx->n;
    vector* v = &mtx->values;

    int row = 0, column = 0;
    int i = 2;
    bool stop = false;

    if (size(v) == 2 && get(v, 0) == -1){
        for (int a = 0; a < m; ++a){
            print_zeroes(n);
            printf("\n");
        }
        return;
    }

    int f_row = (int) get(v, 1);
    if (f_row != 0){
        while (row != f_row){
            print_zeroes(n);
            ++row;
            printf("\n");
        }
    }

    while (!stop && i <= size(v)){
        double flag = get(v, i);
        if (flag == -1){
            print_zeroes(n - column);
            printf("\n");
            if (get(v, i + 1) == -1){
                stop = true;
            } else {
                int n_row = (int) get(v, i + 1);
                while (row + 1 != n_row){
                    print_zeroes(n);
                    ++row;
                    printf("\n");
                }
                row = n_row;
            }
            column = 0;
            i += 2;
        } else {
            double elem = get(v, i + 1);
            print_zeroes((int) flag - column);
            printf("\033[33m%.1lf\033[0m ", elem);
            column = (int) flag + 1;
            i += 2;
        }

    }
    while (row + 1 != m){
        print_zeroes((int) n);
        printf("\n");
        ++row;
    }
    printf("\n");

}

void print_vector(matrix* mtx){
    for (int i = 0; i < size(&mtx->values); ++i){
        printf("%.1lf ", get(&mtx->values, i));
    }
    printf("\n");
}

bool in(double elem, vector* v){
    for (int i = 0; i < size(v); ++i){
        if (elem == get(v, i)){
            return true;
        }
    }
    return false;
}

void refactor_matrix(double elem, matrix* mtx, vector* iid, vector* jid){

    int m = mtx->m;
    int n = mtx->n;
    vector* v = &mtx->values;

    int i = 2;
    bool stop = false;
    double row = 0, column = 0;

    while (!stop && i <= size(v)){
        double flag = get(v, i);
        if (flag == -1){
            if (get(v, i + 1) == -1){
                stop = true;
            }
            column = 0;
            row = get(v, i + 1);
            i += 2;
        } else {
            column = flag;
            if (in(column, iid) || in(row, jid)){
                set(v, i + 1, get(v, i + 1) / elem);
            }
            i += 2;
        }
    }

}

void solve(double search, matrix* mtx){

    int m = mtx->m;
    int n = mtx->n;
    vector* v = &mtx->values;

    vector result;
    vector* r = & result;
    create(r);
    double dx = DBL_MAX;

    int i = 2;
    bool stop = false;
    bool found = false;

    vector i_indexes_first, j_indexes_first;
    vector *iidf = &i_indexes_first, *jidf = &j_indexes_first;
    vector i_indexes_second, j_indexes_second;
    vector *iids = &i_indexes_second, *jids = &j_indexes_second;
    create(iidf); create(jidf); create(iids); create(jids);

    double row = 0, column = 0;

    while (!stop && i <= size(v)){
        double flag = get(v, i);
        if (flag == -1){
            if (get(v, i + 1) == -1){
                stop = true;
            }
            row = get(v, i + 1);
            i += 2;
        } else {
            column = flag;
            double num = get(v, i + 1);
            if (fabs(search - num) <= dx){
                found = true;
                if (size(r) != 0){
                    double cmp = get(r, 0);
                        if (fabs(cmp - search) == fabs(num - search)){
                            //append(r, num);
                            if (cmp != num){
                                if (size(r) == 1){
                                    append(r, num);
                                }
                                append(iids, column);
                                append(jids, row);
                            } else {
                                append(iidf, column);
                                append(jidf, row);
                            }
                        } else {
                            clear(r);
                            clear(iidf); clear(jidf);
                            clear(iids); clear(jids);
                            append(r, num);
                            append(iidf, column);
                            append(jidf, row);
                        }
                    } else {
                        append(r, num);
                        append(iidf, column);
                        append(jidf, row);
                    }
                dx = fabs(num - search);
            }
            i += 2;
        }
    }

    if (!found){
        printf("\033[31;3mError:\033[0m: element not found. Try again.\n");
        scanf("%lf", &search);
        solve(search, mtx);
    } else {
        refactor_matrix(get(r, 0), mtx, iidf, jidf);
        if (size(r) == 2){
            refactor_matrix(get(r, 1), mtx, iids, jids);
        }
    }

    print_matrix(mtx);

}


