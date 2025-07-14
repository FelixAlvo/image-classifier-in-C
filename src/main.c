#include "neural_net.h"
#include "layer.h"
#include "config.h"
#include "utils_log.h"
#include "utils_math.h"
#include "image_loader.h"
#include "stdio.h"
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

int main() {
    // Load input image
    Image* img = il_load_pgm("images/resized.pgm");
    if (!img || img->pixels == NULL) {
        log_error("failed to load training image");
        return 1;
    }

    int input_size = img->width * img->height;
    float* input = malloc(sizeof(float) * input_size);
    for (int i = 0; i < input_size; i++) {
        input[i] = math_normalize((float)img->pixels[i], img->maxval);
    }

    // Label: 1 for cat → [1.0, 0.0]
    float target[2] = {1.0f, 0.0f};

    // Create network
    int sizes[] = {input_size, 64, 2};
    NeuralNetwork* nn = create_nn(3, sizes);
    nn_init_weights_uniform(nn, -0.5f, 0.5f, RANDOM_WEIGHTS_SEED, RANDOM_BIAS_SEED);

    log_info("input_size = %d", input_size);
    log_info("image: %dx%d", img->width, img->height);

    // Train for a few epochs
    float learning_rate = 0.1f;
    for (int epoch = 0; epoch < 1000; epoch++) {
        nn_forward(nn, input);
        int last = nn->num_layers - 2;
        float loss = math_loss_mse(nn->layers[last]->outputs, target, 2);
        nn_backprop(nn, target, learning_rate);

        if (epoch % 100 == 0) {
            log_info("epoch %d, loss = %f", epoch, loss);
        }
    }

    // Final output
    printf("Final output: [");
    for (int i = 0; i < 2; i++) {
        printf("%f", nn->layers[2 - 1]->outputs[i]);
        if (i < 1) printf(", ");
    }
    printf("]\n");

    // Cleanup
    il_free_image(img);
    free(input);
    free_nn(nn);
    return 0;
}
