#include <stdio.h>
#include "config.h"
#include "layer.h"
#include "utils_math.h"
#include "utils_log.h"
#include "neural_net.h"
#include <stdlib.h>

void free_nn(NeuralNetwork* nn){
    if (nn){
        for (int i = 0; i < nn->num_layers - 1; i++) {
            free_layer(nn->layers[i]);
        }
        free(nn->layers);
        free(nn);
    }
}

NeuralNetwork* create_nn(int num_layers, int* layer_sizes){ 
    NeuralNetwork* nn = malloc(sizeof(NeuralNetwork));
    nn->num_layers = num_layers;

    nn->layers = malloc(sizeof(Layer*)*num_layers);

    for (int i = 0; i < num_layers - 1; i++){ // since the output layer doesnt really count as a layer, we only need n-1 acutal layers in the array
        int input_size = layer_sizes[i];
        int output_size = layer_sizes[i + 1];
        nn->layers[i] = create_layer(input_size, output_size);
        if (!nn->layers[i]) {
            log_error("create_layer failed at index %d", i);
            free_nn(nn);
            return NULL;
        }
    }
    
    return nn;
}

void nn_forward(NeuralNetwork* nn, float* input){
    layer_forward(nn->layers[0], input);
    for (int i = 1; i < nn->num_layers - 1; i++){ 
        layer_forward(nn->layers[i], nn->layers[i-1]->outputs);
    }
}

void nn_init_weights_uniform(NeuralNetwork* nn, float min, float max, bool random_weights, bool random_bias) {
    for (int i = 0; i < nn->num_layers - 1; i++) {
        Layer* layer = nn->layers[i];

        for (int j = 0; j < layer->output_size * layer->input_size; j++) {
            layer->weights[j] = math_rand_range(min, max, random_weights);
        }

        for (int j = 0; j < layer->output_size; j++) {
            layer->biases[j] = math_rand_range(min, max, random_bias);
        }
    }
}

void nn_backprop(NeuralNetwork* nn, const float* target, float learning_rate){
    int last = nn->num_layers-2;

    layer_backward_output(nn->layers[last], target);

    for (int i = last-1; i>= 0; i--){
        layer_backward_hidden(nn->layers[i], nn->layers[i+1]);
    }

    for (int i = 0; i < last; i++){
        layer_apply_gradients(nn->layers[i], learning_rate);
    }
}
