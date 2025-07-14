#ifndef IMAGE_TYPES_H
#define IMAGE_TYPES_H

typedef struct {
    int width;
    int height;
    int maxval;
    unsigned char* pixels;
} Image;

#endif