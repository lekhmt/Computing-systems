#ifndef _SORT_H
#define _SORT_H

#include "table.h"

void selection_sort(); // линейный выбор с обменом
void bubble_sort();    // метод пузырька
void shaker_sort();    // шейкер-сортировка
void insertion_sort(); // метод простой вставки
void shell_sort();     // сортировка Шелла

void quick_sort(int left, int right);     // быстрая сортировка Хоара
void heap_sort();      // пирамидальная сортировка
void smooth_sort();    // гладкая сортировка

#endif
