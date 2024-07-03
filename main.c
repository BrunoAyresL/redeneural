#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "value_type.h"
#include "arraylist.h"
#include "topo_sort.h"
#include "neural_network.h"

int main() {
    int l[3] = {1,10,10};
    nn neural_net = create_nn(l, 3, 1);
    show_nn(neural_net);
    /*
    value* a = create_value(0.2, NULL, NULL, 'e');
    value* vals[1] = {a};
    value* e = neuron_output(neural_net.layers[0].neurons[0], vals);
    printf("\n\nData\t\tGradient\tCreated by operation");
    show(*e);
    show(*(nn_output(neural_net, vals)[0]));
    */

    
    // [[1],[2],[3],[4]]
    /*
    inputs[0][0] = create_value(5.0, NULL, NULL, 'i');
    inputs[1][0] = create_value(0.5, NULL, NULL, 'i');
    inputs[2][0] = create_value(0.5, NULL, NULL, 'i');
    inputs[3][0] = create_value(13.0, NULL, NULL, 'i');
    
    
    targets[0][0] = create_value(1.0, NULL, NULL, 'f');
    targets[1][0] = create_value(1.0, NULL, NULL, 'f');
    targets[2][0] = create_value(1.0, NULL, NULL, 'f');
    targets[3][0] = create_value(1.0, NULL, NULL, 'f');
    */
    value* inputs[300][1];
    value* targets[300][1];
    for (int i = 0; i < 300; i++) {
        double j = (double)i;
        inputs[i][0] = create_value(j / 30.0, NULL, NULL, 'k');   
        targets[i][0] = create_value(j / 60.0, NULL, NULL, 'g');
    }
    // 2pi 
    value* predicts[300];
    for(int j = 0; j < 50; j++) {
        //printf("\nInputs\t\tPredicts\tTargets");
        for (int i = 0; i < 300; i++) {
            predicts[i] = nn_output(neural_net, inputs[i])[0];
            //printf("\n%f\t%f\t%f", inputs[i][0]->data, predicts[i]->data, targets[i][0]->data);
        }
        
        value* loss = loss_function(neural_net, predicts, targets, 300);
        printf("\nLoss:\t%f", loss->data);

        zero_grad(&neural_net);
        backpropagation(loss);
        update_parameters(&neural_net, 0.001);
    
    }
   
    return 0;
}