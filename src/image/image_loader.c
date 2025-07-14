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

Image* il_load_pgm(const char* filepath){
    Image* pgm_image = malloc(sizeof(Image));
    FILE* file;
    file = fopen(filepath, "r");
    if (file == NULL){
        log_error("error reading file: %c", filepath);
        il_free_image(pgm_image);
        return;
    }

    char magic_number[4];
    fscanf(file, "%2s", magic_number);
    if (strcmp(magic_number, MAGIC_NUMBER_P2) != 0) {
        log_info("Invalid magic number for image %s\nMagic number: %s", filepath, magic_number);
        return;
    }
    fgetc(file); // skip the new line character \n

    char ch = fgetc(file);

    int exit_check = 0;

    while (exit_check < LOOP_MAX_ITERATIONS) { // ignore all comments
        exit_check++;
        if (ch == '#'){
            while (fgetc(file) != '\n');
            ch = fgetc(file);
        } else {
            ungetc(ch, file);
            break;
        }
    }

    int width, height, maxval;
    fscanf(file, "%d %d", &width, &height);
    fscanf(file, "%d", &maxval);

    pgm_image->width = width;
    pgm_image->height = height;
    
    int size = width * height;

    pgm_image->pixels = malloc(size);
    for (int i = 0; i < size; i++){
        int pixel;
        fscanf(file, "%d", &pixel);
        pgm_image->pixels[i] = (unsigned char) pixel;
    }

    fclose(file);
    return pgm_image;
}