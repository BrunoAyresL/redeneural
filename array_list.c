#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"

arrlist* create_arrlist(int capacity) {
    arrlist* list = (arrlist*) malloc(sizeof(arrlist));
    
    list->data = (value**) malloc(capacity * sizeof(value*));

    list->size = 0;
    list->capacity = capacity;
}

void append_arrlist(arrlist* list, value* val) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->data = (value**) realloc(list->data, list->capacity * sizeof(value*));
    }
    
    list->data[list->size] = val;
    list->size++;
}

void free_arrlist(arrlist* list) {
    free(list->data);
    free(list);
}