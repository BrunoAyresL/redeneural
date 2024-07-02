#include <stdio.h>
#include <stdlib.h>
#include "value_type.c"
#include "rng.c"

typedef struct Neuron {
    int n_inputs;
    value* bias;
    value** weights;
} neuron;

typedef struct Layer {
    int n_neurons;
    neuron* neurons;
} layer;

typedef struct Neural_Network {
    int n_layers;
    int n_outputs;
    layer* layers;
} nn;

neuron create_neuron(int n_inputs) {
    neuron n;
    n.n_inputs = n_inputs;
    n.bias = create_value(1.0, NULL, NULL, 'b');
    n.weights = (value**) malloc(n_inputs * sizeof(value));

    new_seed();
    for (int i = 0; i < n_inputs; i++) {
        n.weights[i] = create_value(rand_double(), NULL, NULL, 'w');
    }
    return n;
}

value* neuron_output(neuron n, value** x) {
     // x length == n.n_inputs
     
    value** vals = (value**) malloc(n.n_inputs * sizeof(value));
    int i = 0;
    for (; i < n.n_inputs; i++) {
        vals[i] = multiply(n.weights[i], x[i]);
    }
    
    value* result = (value*)malloc(sizeof(value));
    for (int j = 0; j < i; j++) {
        result = add(result, vals[j]);
    }
    result = tanh_value(result);
    return result;
}

value** layer_output(layer l, value** x) {
    // x length == l.neurons[0].n_inputs
    value** result = (value**) malloc(l.n_neurons * sizeof(value));
    for (int i = 0; i < l.n_neurons; i++) {
        result[i] = neuron_output(l.neurons[i], x);
    }
    return result;
}

value** nn_output(nn n_net, value** x) {
    value** result = (value**) malloc(n_net.n_outputs * sizeof(value));
    result = x;
    for (int i = 0; i < n_net.n_layers; i++) {
        result = layer_output(n_net.layers[i], result);
    }
    return result;
}


layer create_layer(int n_inputs, int n_outputs) {
    layer l;
    l.n_neurons = n_outputs;
    l.neurons = (neuron*) malloc(n_outputs * sizeof(neuron));
    for (int i = 0; i < l.n_neurons; i++) {
        l.neurons[i] = create_neuron(n_inputs);
    }  
    return l;
}

nn create_nn(int* layers, int n_layers, int n_outputs) {
    nn n_net;
    n_net.n_layers = n_layers;
    n_net.n_outputs = n_outputs;
    n_net.layers = (layer*) malloc(n_layers * sizeof(layer));

    for (int i = 0; i < n_layers - 1; i++) {     
        n_net.layers[i] = create_layer(layers[i], layers[i + 1]);
    }
    n_net.layers[n_layers - 1] = create_layer(layers[n_layers - 1], n_outputs);
    
    return n_net;
}

void show_nn(nn n) {
    printf("\nInput");
    for (int i = 0; i < n.n_layers - 1; i++) {
        printf("\tLayer %d", i + 1);
    }
    printf("\tOutput");
    printf("\n%d", n.layers[0].neurons[0].n_inputs);
    for (int i = 0; i < n.n_layers; i++) {
        printf("\t%d", n.layers[i].n_neurons);
    }

}

value* loss_function() {

}

int main() {
    int l[5] = {1,8,8,8,2};
    nn neural_net = create_nn(l, 5, 1);
    show_nn(neural_net);

    value* a = create_value(0.2, NULL, NULL, 'e');
    value* vals[1] = {a};
    value* e = neuron_output(neural_net.layers[0].neurons[0], vals);
    printf("\n\nData\t\tGradient\tCreated by operation");
    show(*e);
    show(*(nn_output(neural_net, vals)[0]));

    for (int i = 0; i < 4; i++) {
        
    }



    return 0;
}