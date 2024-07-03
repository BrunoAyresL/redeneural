#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "value_type.h"
#include "arraylist.h"

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

value* neuron_output(neuron n, value** x);
value** layer_output(layer l, value** x);
value** nn_output(nn n_net, value** x);
layer create_layer(int n_inputs, int n_outputs);
nn create_nn(int* layers, int n_layers, int n_outputs);
void show_nn(nn n);
void zero_grad(nn* n_net);
void update_parameters(nn* n_net, double l_rate);
value* loss_function(nn n_net, value** input, value** target, int size);




#endif // NEURAL_NETWORK_H
