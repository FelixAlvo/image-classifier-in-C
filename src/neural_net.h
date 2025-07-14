#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include "layer.h"
#include <stdbool.h>

typedef struct{
    int num_layers;
    Layer** layers;
}NeuralNetwork;

void free_nn(NeuralNetwork* nn);
NeuralNetwork* create_nn(int num_layers, int* layer_sizes);
void nn_forward(NeuralNetwork* nn, float* input);
void nn_init_weights_uniform(NeuralNetwork* nn, float min, float max, bool random_weights, bool random_bias);
void nn_backprop(NeuralNetwork* nn, const float* target, float learning_rate);

#endif