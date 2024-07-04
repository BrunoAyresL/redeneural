#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "value_type.h"
#include "arraylist.h"
#include "topo_sort.h"
#include "neural_network.h"

int main() {
    int l[3] = {2,8,4};
    nn neural_net = create_nn(l, 3, 1);
    show_nn(neural_net);

    value* inputs[4][2];
    value* targets[4][1];

    inputs[0][0] = create_value(0.0, NULL, NULL, 'i');
    inputs[0][1] = create_value(0.0, NULL, NULL, 'i');

    inputs[1][0] = create_value(1.0, NULL, NULL, 'i');
    inputs[1][1] = create_value(0.0, NULL, NULL, 'i');

    inputs[2][0] = create_value(0.0, NULL, NULL, 'i');
    inputs[2][1] = create_value(1.0, NULL, NULL, 'i');

    inputs[3][0] = create_value(1.0, NULL, NULL, 'i');
    inputs[3][1] = create_value(1.0, NULL, NULL, 'i');

    targets[0][0] = create_value(0.0, NULL, NULL, 'g');

    targets[1][0] = create_value(1.0, NULL, NULL, 'g');

    targets[2][0] = create_value(1.0, NULL, NULL, 'g');

    targets[3][0] = create_value(0.0, NULL, NULL, 'g');
    
    value* predicts[4];
    for(int j = 0; j < 100000; j++) {
        //printf("\nPredicts\tTargets");
        for (int i = 0; i < 4; i++) {
            predicts[i] = nn_output(neural_net, inputs[i])[0];
            //printf("\n%f\t%f", predicts[i]->data, targets[i][0]->data);
        }
        
        value* loss = loss_function(neural_net, predicts, targets, 4);
        if (j % 10000 == 0) {
            printf("\n%d -> Loss:\t%f", j, loss->data);
        }


        zero_grad(&neural_net);
        backpropagation(loss);
        update_parameters(&neural_net, 0.02);
        if (j == 100000 - 1) {
            printf("\n\nPredicts\tTargets");
            for (int i = 0; i < 4; i++) {
            printf("\n%f\t%f", predicts[i]->data, targets[i][0]->data);
            }  
            printf("\n\nLoss:\t%f", loss->data);  
        }
    }

   
    return 0;
}