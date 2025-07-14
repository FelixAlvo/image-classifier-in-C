#ifndef LAYER_H
#define LAYER_H

typedef struct{
    int input_size;
    int output_size;

    float* deltas;
    float* inputs;

    float* weights;
    float* biases;
    float* outputs;
}Layer;

void free_layer(Layer* layer);
Layer* create_layer(int input_size, int output_size);
void layer_forward(Layer* layer, float* input);

void layer_backward_output(Layer* layer, const float* target);
void layer_backward_hidden(Layer* layer, Layer* next_layer);
void layer_apply_gradients(Layer* layer, float learning_rate);

#endif