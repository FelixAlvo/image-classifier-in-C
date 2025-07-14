#include "image_loader.h"
#include "config.h"
#include "data.h"
#include "utils_math.h"
#include "utils_log.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <dirent.h>

void create_dataset_directory(){
    if (mkdir("data_set", 0755) == -1 && errno != EEXIST){
        log_error("Failed to create data_set root directory");
        return;
    }
    if (mkdir("data_set/cat", 0755) == -1 && errno != EEXIST) {
        log_error("Failed to create directory");
        return;
    }
    if (mkdir("data_set/dog", 0755) == -1 && errno != EEXIST) {
        log_error("Failed to create directory");
        return;
    }
}

void free_te(TrainingExample* te){
    if (te){
        free(te->input);
        free(te->target);
    }
}

TrainingExample load_data_to_TE(Image* image, float* target, int target_size) {
    TrainingExample te;
    int size = image->width * image->height;

    te.input = malloc(sizeof(float) * size);
    te.target = malloc(sizeof(float) * target_size);

    for (int i = 0; i < size; i++) {
        te.input[i] = math_normalize((float) image->pixels[i], image->maxval);
    }

    memcpy(te.target, target, sizeof(float) * target_size);
    return te;
}



Dataset* load_dataset(const char* base_dir){
    int max = 100;
    int current = 0;

    const char* classes[] = { "cat", "dog" };

    Dataset* dataset = malloc(sizeof(Dataset));
    dataset->examples = malloc(sizeof(TrainingExample)*max);

    for(int c = 0; c < 2; c++){
        char path[256];
        snprintf(path, sizeof(path), "%s/%s", base_dir, classes[c]);

        DIR* dir = opendir(path);
        if (!dir){
            log_error("failed to open dir: %s", path);
            continue;
        }
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL){
            if (strstr(entry->d_name, ".pgm") == NULL) continue;

            char filepath[512];
            snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);

            Image* img = il_load_pgm(filepath);
            if (!img) continue;

            float target[2] = {0.0f, 0.0f};
            target[c] = 1.0f;

            if (current>=max){
                max *=2;
                TrainingExample* temp = realloc(dataset->examples, sizeof(TrainingExample) * max);
                if (!temp) {
                    log_error("realloc failed!");
                    break;
                }
                dataset->examples = temp;
            }

            dataset->examples[current] = load_data_to_TE(img, target, 2);

            current++;
        }
        log_info("Loaded %d examples from class: %s", current, classes[c]);
        closedir(dir);
    }

    dataset->count = current;
    return dataset;
}

void free_dataset(Dataset* dataset) {
    if (!dataset) return;

    for (int i = 0; i < dataset->count; i++) {
        free(dataset->examples[i].input);
        free(dataset->examples[i].target);
    }

    free(dataset->examples);
    free(dataset);
}

void shuffle_dataset(Dataset* dataset) {
    for (int i = dataset->count - 1; i > 0; i--) {
        int j = math_rand_i(0, i, RANDOM_SEED);

        TrainingExample temp = dataset->examples[i];
        dataset->examples[i] = dataset->examples[j];
        dataset->examples[j] = temp;
    }
}