#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "value_type.h"

typedef struct ArrayList {
    int size;
    int capacity;
    value** data;
} arrlist;

arrlist* create_arrlist(int capacity);
void append_arrlist(arrlist* list, value* val);
void free_arrlist(arrlist* list);

#endif // ARRAY_LIST_H
