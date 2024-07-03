#ifndef TOPO_SORT_H
#define TOPO_SORT_H
        
#include "value_type.h"
#include "arraylist.h"

void backpropagation(value* loss);
void search_values(value* val, arrlist* visited, arrlist* topologic);
int is_visited(value* val, arrlist* visited);

#endif // TOPO_SORT_H
