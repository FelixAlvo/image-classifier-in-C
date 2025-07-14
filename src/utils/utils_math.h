#ifndef UTILS_MATH_H
#define UTILS_MATH_H

#include <stdbool.h>
#include <stdint.h>


// neural network node functions
float math_sigmoid(float x);
float math_sigmoid_derivative(float x);
float math_relu(float x);
float math_relu_derivative(float x);
float math_loss_mse(const float* predicted, const float* expected, int length);

// random number functions
float math_rand_f(bool random_seed);
float math_rand_range(float min, float max, bool random_seed);

// vector array operations
float math_dot_prod(const float* a, const float* b, int length);
void math_add_arrays(const float* a, const float* b, float* out, int length);
void math_scale_array(float* array, float scalar, int length);

// matrix operations
void math_mat_mul(const float* A, const float* B, float* out, int m, int n, int p);
void math_transpose(const float* in, float* out, int rows, int cols);


// extras
float math_normalize(uint32_t value, uint32_t normalization_value);

#endif