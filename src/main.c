#include "neural_net.h"
#include "layer.h"
#include "config.h"
#include "utils_log.h"
#include "utils_math.h"
#include "image_loader.h"
#include "data.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

int main() {
    Dataset* dataset = load_dataset("data_set");
    if (!dataset || dataset->count == 0) {
        log_error("Failed to load dataset");
        return 1;
    }

    log_info("Loaded %d training examples", dataset->count);

    // Create neural network
    int input_size = 64 * 64;  // match your images
    int sizes[] = { input_size, 64, 2 };
    NeuralNetwork* nn = create_nn(3, sizes);
    nn_init_weights_uniform(nn, -0.5f, 0.5f, true, true);

    float learning_rate = LEARNING_RATE;
    int epochs = EPOCHS;

    for (int epoch = 0; epoch < epochs; epoch++) {
        shuffle_dataset(dataset);
        float total_loss = 0.0f;

        // Loop over all training examples
        for (int i = 0; i < dataset->count; i++) {
            TrainingExample* ex = &dataset->examples[i];

            nn_forward(nn, ex->input);
            total_loss += math_loss_mse(nn->layers[2 - 1]->outputs, ex->target, 2);
            nn_backprop(nn, ex->target, learning_rate);
        }

        log_info("Epoch %d - avg loss: %f", epoch, total_loss / dataset->count);
    }

    free_dataset(dataset);

    Image* test_img = il_load_pgm("data_set/dog/dog1.pgm");
    float* input = malloc(sizeof(float) * (test_img->width * test_img->height));
    for (int i = 0; i < test_img->width * test_img->height; i++) {
        input[i] = (float)test_img->pixels[i] / test_img->maxval;
    }

    int predicted = nn_predict(nn, input);
    printf("Prediction: %s\n", predicted == 0 ? "cat" : "dog");

    free(input);
    il_free_image(test_img);
    
    return 0;
}
