#include <stdbool.h>
#include <string.h>
#include "../headers/sort.h"
#include "../headers/table.h"

#define T table_element

int table_size;
table_element table[TABLE_CAPACITY];

bool cmp(T lhs, T rhs){
    return lhs.key <= rhs.key;
}

void bubble_sort(){
    for (int i = 0; i < table_size; ++i){
        for (int j = 0; j < table_size - i - 1; ++j){
            T lhs = table[j];
            T rhs = table[j + 1];
            if (!cmp(lhs, rhs)){
                table[j] = rhs;
                table[j + 1] = lhs;
            }
        }
    }
}

void selection_sort(){
    long long max;
    int idx;
    for (int i = 0; i < table_size; ++i){
        for (int j = 0; j < table_size - i; ++j){
            if (j == 0){
                max = table[j].key;
                idx = 0;
                continue;
            }
            if (table[j].key > max){
                max = table[j].key;
                idx = j;
            }
        }
        T tmp = table[table_size - i - 1];
        table[table_size - i - 1] = table[idx];
        table[idx] = tmp;
    }
}

void shaker_sort(){
    int left = 0;
    int right = table_size - 1;
    bool flag = true;
    while ((left < right) && flag){
        flag = false;
        for (int i = left; i < right; ++i){
            T lhs = table[i];
            T rhs = table[i + 1];
            if (!cmp(lhs, rhs)){
                table[i] = rhs;
                table[i + 1] = lhs;
                flag = true;
            }
        }
        --right;
        for (int i = right; i > left; --i){
            T lhs = table[i];
            T rhs = table[i + 1];
            if (!cmp(lhs, rhs)){
                table[i] = rhs;
                table[i + 1] = lhs;
                flag = true;
            }
        }
        ++left;
    }
}

void insertion_sort(){
    for (int i = 1; i < table_size; ++i){
        T tmp = table[i];
        int j = i - 1;
        while (j >= 0 && !cmp(table[j], tmp)){
            table[j + 1] = table[j];
            table[j] = tmp;
            --j;
        }
    }
}

void shell_sort(){
    for (int s = table_size / 2; s > 0; s /= 2){
        for (int i = 0; i < table_size; ++i){
            for (int j = i + s; j < table_size; j += s){
                if (!cmp(table[i], table[j])){
                    T tmp = table[j];
                    table[j] = table[i];
                    table[i] = tmp;
                }
            }
        }
    }
}

void quick_sort(int left, int right){

    int i, j, pivot;
    T tmp;

    if (left < right){
        pivot = left;
        i = left;
        j = right;
        while (i < j){
            while (cmp(table[i], table[pivot]) && i < right){
                ++i;
            }
            while (!cmp(table[j], table[pivot])) {
                --j;
            }
            if (i < j){
                tmp = table[i];
                table[i] = table[j];
                table[j] = tmp;
            }
        }
        tmp = table[pivot];
        table[pivot] = table[j];
        table[j] = tmp;
        quick_sort(left, j - 1);
        quick_sort(j + 1, right);
    }

}

