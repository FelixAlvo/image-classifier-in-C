#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H
#include "image_types.h"
#include <stdlib.h>

Image* il_load_pgm(const char* filepath);
void il_free_image(Image* img);
#endif