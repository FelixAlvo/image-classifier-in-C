#include "layer.h"
#include "utils_math.h"
#include "utils_log.h"
#include <stdlib.h>
#include <string.h>


void free_layer(Layer* layer){
    if (layer){
        free(layer->weights);
        free(layer->biases);
        free(layer->outputs);
        free(layer->deltas);
        free(layer->inputs);
        free(layer);
    }
}


Layer* create_layer(int input_size, int output_size){
    Layer* layer = malloc(sizeof(Layer));
    layer->input_size = input_size;
    layer->output_size = output_size;

    layer->weights = malloc(sizeof(float) * input_size * output_size);
    layer->biases = malloc(sizeof(float) * output_size);
    layer->outputs = malloc(sizeof(float) * output_size);
    layer->deltas = malloc(sizeof(float) * output_size);

if (!layer || !layer->weights || !layer->biases || !layer->outputs || !layer->deltas) {
    log_error("Failed to allocate memory for layer");
    free_layer(layer);  // cleanup
    return NULL;
}

    return layer;
}

void layer_forward(Layer* layer, float* input){
    math_mat_mul(layer->weights, input, layer->outputs, layer->output_size, layer->input_size, 1);

    float* biased_output = malloc(sizeof(float) * layer->output_size);
    if (!biased_output) {
        log_error("Failed to allocate biased_output");
        return;
    }
    math_add_arrays(layer->outputs, layer->biases, biased_output, layer->output_size);

    for (int i = 0; i < layer->output_size; i++) {
        layer->outputs[i] = math_sigmoid(biased_output[i]);
    }

    if (layer->inputs == NULL) {
        layer->inputs = malloc(sizeof(float) * layer->input_size);
    }
    memcpy(layer->inputs, input, sizeof(float) * layer->input_size);

    free(biased_output);
}

void layer_backward_output(Layer* layer, const float* target) {
    for (int i = 0; i < layer->output_size; i++) {
        float output = layer->outputs[i];
        float error = output - target[i];
        layer->deltas[i] = error * output * (1.0f - output);
    }
}

void layer_backward_hidden(Layer* layer, Layer* next_layer) {
    for (int i = 0; i < layer->output_size; i++) {
        float sum = 0.0f;

        for (int j = 0; j < next_layer->output_size; j++) {
            int weight_index = j * layer->output_size + i;
            sum += next_layer->weights[weight_index] * next_layer->deltas[j];
        }

        float out = layer->outputs[i];
        layer->deltas[i] = sum * out * (1.0f - out);
    }
}

void layer_apply_gradients(Layer* layer, float learning_rate) {
    for (int i = 0; i < layer->output_size; i++) {
        for (int j = 0; j < layer->input_size; j++) {
            int index = i * layer->input_size + j;
            layer->weights[index] -= learning_rate * layer->deltas[i] * layer->inputs[j];
        }
        layer->biases[i] -= learning_rate * layer->deltas[i];
    }
}
