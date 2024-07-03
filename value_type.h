#ifndef VALUE_TYPE_H
#define VALUE_TYPE_H

typedef struct Value {
    double data;
    double grad;
    char op;
    int n_prev;
    struct Value* prev[2];
    void (*backward)(struct Value*);
} value;

value* create_value(double data, value* prev1, value* prev2, char op);
void null_backward(value* a);
void add_backward(value* result);
value* add(value* a, value* b);
void multiply_backward(value* result);
value* multiply(value* a, value* b);
void relu_backward(value* result);
value* relu(value* a);
void tanh_backward(value* result);
value* tanh_value(value* a);
void show(value a);

#endif // VALUE_TYPE_H