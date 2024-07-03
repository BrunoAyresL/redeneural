#include <stdio.h>
#include "topo_sort.h"

void backpropagation(value* loss) {
    arrlist* topologic = create_arrlist(32);
    arrlist* visited = create_arrlist(32); 

    search_values(loss, visited, topologic);
    loss->grad = 1;

    for (int i = topologic->size - 1; i >= 0; i--) {
        topologic->data[i]->backward(topologic->data[i]);
    }
    free_arrlist(topologic);
    free_arrlist(visited);
}

void search_values(value* val, arrlist* visited, arrlist* topologic) {
    if (!is_visited(val, visited)) {

        append_arrlist(visited, val);

        for (int i = 0; i < val->n_prev; i++) {
            search_values(val->prev[i], visited, topologic);
        }
        append_arrlist(topologic, val);
    }
} 

int is_visited(value* val, arrlist* visited) {
    for (int i = 0; i < visited->size; i++) {
        if (val == visited->data[i]) {
            return 1;
        }
    }
    return 0;
}