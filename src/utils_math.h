#ifndef UTILS_MATH_H
#define UTILS_MATH_H


// neural network node functions
float sigmoid(float x);
float sigmoid_derivative(float x);
float relu(float x);
float relu_derivative(float x);
float tanh_fn(float x);
float tanh_fn_derivative(float x);

// random number functions
float rand_f(uint32_t set_seed);
float rand_range(float min, float max, uint32_t set_seed);

// vector array operations
float dot_prod(const float* a, const float* b, int length);
void add_arrays(const float* a, const float* b, float* out, int length);
void scale_array(float* araray, float scalar, int length);

// matrix operations
void mat_mul(const float* A, const float* b, float* out, int m, int n, int p);
void transpose(const float* in, float* out, int rows, int cols);

// extras
float normalize(uint32_t value, uint32_t normalization_value);

#endif