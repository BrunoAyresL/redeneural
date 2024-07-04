#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "neural_network.h"
#include "rng.c"

neuron create_neuron(int n_inputs) {
    neuron n;
    n.n_inputs = n_inputs;
    n.bias = create_value(0.0, NULL, NULL, 'b');
    n.weights = (value**) malloc(n_inputs * sizeof(value));

    if (n.weights == NULL) {
        perror("Failed weights malloc");
        exit(EXIT_FAILURE);
    }

    new_seed();
    for (int i = 0; i < n_inputs; i++) {
        n.weights[i] = create_value(rand_double(), NULL, NULL, 'w');
    }
    return n;
}

value* neuron_output(neuron n, value** x) {
     // x length == n.n_inputs
    
    value** vals = (value**) malloc(n.n_inputs * sizeof(value));

    if (vals == NULL) {
        perror("Failed vals malloc");
        exit(EXIT_FAILURE); 
    }

    int i = 0;
    for (; i < n.n_inputs; i++) {
        vals[i] = multiply(n.weights[i], x[i]);
    }
    value* result = create_value(0.0, NULL, NULL, 'o');
    for (int j = 0; j < i; j++) {
        result = add(result, vals[j]);
    }

    free(vals);
    result = tanh_value(result);
    return result;
}

value** layer_output(layer l, value** x) {
    value** result = (value**) malloc(l.n_neurons * sizeof(value));

    if (result == NULL) {
        perror("Failed layers malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < l.n_neurons; i++) {
        result[i] = neuron_output(l.neurons[i], x);
    }
    return result;
}

value** nn_output(nn n_net, value** x) {
    value** result = x;
    for (int i = 0; i < n_net.n_layers; i++) {
        result = layer_output(n_net.layers[i], result);
    }
    return result;
}


layer create_layer(int n_inputs, int n_outputs) {
    layer l;
    l.n_neurons = n_outputs;
    l.neurons = (neuron*) malloc(n_outputs * sizeof(neuron));

    if (l.n_neurons == 0) {
        perror("Failed layer.n_neurons malloc");
        exit(EXIT_FAILURE);
    }

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

    if (n_net.layers == NULL) {
        perror("Failed nn.layers malloc");
        exit(EXIT_FAILURE);
    }


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

void zero_grad(nn* n_net) {
    for (int i = 0; i < n_net->n_layers; i++) {
        for (int j = 0; j < n_net->layers[i].n_neurons; j++) { 
            n_net->layers[i].neurons[j].bias->grad = 0; 
    
            for (int k = 0; k < n_net->layers[i].neurons[j].n_inputs; k++) {  
                n_net->layers[i].neurons[j].weights[k]->grad = 0;
            }

        }
    }      
}

void update_parameters(nn* n_net, double l_rate) {
    for (int i = 0; i < n_net->n_layers; i++) {
        for (int j = 0; j < n_net->layers[i].n_neurons; j++) {   
            value* bias = n_net->layers[i].neurons[j].bias; 
            bias->data += -l_rate * bias->grad + 0.00001;
    
            for (int k = 0; k < n_net->layers[i].neurons[j].n_inputs; k++) {  
                value* weight = n_net->layers[i].neurons[j].weights[k];
                weight->data += -l_rate * weight->grad + 0.00001;

            }

        }
    }
}

value* loss_function(nn n_net, value** input, value** target, int size) {
    value* loss = create_value(0.0, NULL, NULL, 'l');
    value* minus_one = create_value(-1.0, NULL, NULL, 'e');
    for (int i = 0; i < size; i++) {
        value* temp = add(multiply(minus_one, input[i]), target[i]);
        loss = add(multiply(temp, temp), loss);
    }
    return loss;
}