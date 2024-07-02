#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Value {
    double data;
    double grad;
    char op;
    int n_prev;
    struct Value* prev[2];
    void (*backward)(struct Value*);
} value;

void null_backward(value* a) {

}

value* create_value(double data, value* prev1, value* prev2, char op) {
    value* val = (value*) malloc(sizeof(value));
    val->data = data;
    val->grad = 0;
    val->op = op;
    val->n_prev = 0;

    val->prev[0] = NULL;
    val->prev[1] = NULL;

    if (prev1 != NULL) val->n_prev++;
    if (prev2 != NULL) val->n_prev++;
    val->prev[0] = prev1;
    val->prev[1] = prev2;

    val->backward = null_backward;
    return val;
}

void show(value a) {
    printf("\n%f\t%f", a.data, a.grad);

    if (a.n_prev == 2) {
        printf("\t%f %c %f\t", a.prev[0]->data, a.op, a.prev[1]->data);
    } else if (a.n_prev == 1) {
        printf("\t%f %c\t", a.prev[0]->data, a.op); 
    } else {
        printf("\tNone (%c)", a.op);
    }

}

void add_backward(value* result) {
    result->prev[0]->grad += result->grad;
    result->prev[1]->grad += result->grad;
}

value* add(value* a, value* b) {
    value* result = create_value(a->data + b->data, a, b, '+');
    result->backward = add_backward;
    return result;
}

void multiply_backward(value* result) {
    result->prev[0]->grad += result->grad * result->prev[1]->data;
    result->prev[1]->grad += result->grad * result->prev[0]->data;
}

value* multiply(value* a, value* b) {
    value* result = create_value(a->data * b->data, a, b, '*');
    result->backward = multiply_backward;
    return result;
}

void tanh_backward(value* result) {
    result->prev[0]->grad += (1 - (result->data * result->data)) * result->grad;
}

value* tanh_value(value* a) {
    value* result = create_value(tanh(a->data), a, NULL, 't');
    result->backward = tanh_backward;
    return result;
}

void backward_pass(value* a) {
    value* topologic[512]; // usar arraylist depois
    int topo_size = 0;
    value* visited[512];  // usar arraylist depois

    search_values(a, visited, 0, topologic, &topo_size);

    a->grad = 1;
    for (int i = topo_size - 1; i >= 0; i--) {
        topologic[i]->backward(topologic[i]);
    }
}

void search_values(value* val, value** visited, int visited_size, value** topologic, int* topo_size) {
    if (!is_visited(val, visited, visited_size)) {
        visited[visited_size] = val;
        visited_size++;
        for (int i = 0; i < val->n_prev; i++) {
            search_values(val->prev[i], visited, visited_size, topologic, topo_size);
        }
        topologic[*topo_size] = val;
        (*topo_size)++;
    }
} 

int is_visited(value* val, value** visited, int visited_size) {
    for (int i = 0; i < visited_size; i++) {
        if (val == visited[i]) {
            return 1;
        }
    }
    return 0;
}
/*
int main() {
    value a = create_value(-0.6, NULL, NULL, '\n');
    value b = create_value(1.1, NULL, NULL, '\n');
    value c = add(&a, &b);
    value d = create_value(0.5, NULL, NULL, '\n');
    value e = multiply(&c, &d);
    value f = tanh_value(&e);
    backward_pass(&f);
    printf("\nData\t\tGradient\tCreated by operation");
    show(f);
    show(e);
    show(d);    
    show(c);
    show(b);
    show(a);


}
*/