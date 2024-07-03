#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "value_type.h"

void null_backward(value* a) {
    (void)a;
}

value* create_value(double data, value* prev1, value* prev2, char op) {
    value* val = (value*) malloc(sizeof(value));
    if (val == NULL) {
        perror("Failed create_value val malloc");
        exit(EXIT_FAILURE);
    }
    val->data = data;
    val->grad = 0;
    val->op = op;
    val->n_prev = 0;

    val->prev[0] = prev1;
    val->prev[1] = prev2;

    if (prev1 != NULL) val->n_prev++;
    if (prev2 != NULL) val->n_prev++;

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
        printf("\t(%c)", a.op);
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

void relu_backward(value* result) {
    if (result->data < 0) {
        result->prev[0]->grad = 0;
    } else {
        result->prev[0]->grad += result->grad;
    }
}

value* relu(value* a) {
    double x = a->data;
    if (x < 0.0) {
        x = 0.0;
    }
    value* result = create_value(x, a, NULL, 'r');
    result->backward = relu_backward;
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
