#include "image_loader.h"
#include "image_types.h"
#include "utils_log.h"
#include "config.h"
#include <stdio.h>
#include <string.h>


void il_free_image(Image* img){

    if (img){
        free(img->pixels);
        free(img);
    }
}

Image* il_load_pgm(const char* filepath) {
    Image* pgm_image = malloc(sizeof(Image));
    if (!pgm_image) {
        log_error("Failed to allocate Image struct");
        return NULL;
    }

    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        log_error("Error reading file: %s", filepath);
        free(pgm_image);
        return NULL;
    }

    char magic_number[4];
    if (fscanf(file, "%2s", magic_number) != 1 || strcmp(magic_number, MAGIC_NUMBER_P2) != 0) {
        log_info("Invalid or missing magic number in image: %s", filepath);
        fclose(file);
        free(pgm_image);
        return NULL;
    }
    fgetc(file);

    char ch = fgetc(file);
    int exit_check = 0;

    while (exit_check++ < LOOP_MAX_ITERATIONS) {
        if (ch == '#') {
            while (fgetc(file) != '\n');
            ch = fgetc(file);
        } else {
            ungetc(ch, file);
            break;
        }
    }

    int width, height, maxval;
    if (fscanf(file, "%d %d", &width, &height) != 2 ||
        fscanf(file, "%d", &maxval) != 1) {
        log_error("Failed to read image dimensions or maxval from %s", filepath);
        fclose(file);
        free(pgm_image);
        return NULL;
    }

    pgm_image->width = width;
    pgm_image->height = height;
    pgm_image->maxval = maxval;

    int size = width * height;
    pgm_image->pixels = malloc(size);
    if (!pgm_image->pixels) {
        log_error("Failed to allocate pixel data for %s", filepath);
        fclose(file);
        free(pgm_image);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        int pixel;
        if (fscanf(file, "%d", &pixel) != 1) {
            log_error("Failed to read pixel data at index %d in %s", i, filepath);
            free(pgm_image->pixels);
            free(pgm_image);
            fclose(file);
            return NULL;
        }
        pgm_image->pixels[i] = (unsigned char)pixel;
    }

    fclose(file);
    return pgm_image;
}