#ifndef _TABLE_H
#define _TABLE_H

#define TABLE_CAPACITY 512
#define STRING_CAPACITY 256

typedef struct {
    long long key;
    char value[STRING_CAPACITY];
} table_element;

void preset();

extern table_element table[TABLE_CAPACITY];
extern int table_size;

#endif
