#ifndef CONFIG_H
#define CONFIG_H

// test function macros
#define TEST_ALL 0

#define TEST_MATH_SIGMOID 10
#define TEST_MATH_SIGMOID_DERIVATIVE 11
#define TEST_MATH_RELU 12
#define TEST_MATH_RELU_DERIVATIVE 13

#define TEST_MATH_RAND_F 100
#define TEST_MATH_RAND_RANGE 101

#define TEST_MATH_DOT_PROD 200
#define TEST_MATH_ADD_ARRAYS 201
#define TEST_MATH_SCALE_ARRAY 202

#define TEST_MATH_MAT_MUL 300
#define TEST_MATH_TRANSPOSE 301

// seed logic for PRNG generator
#define RANDOM_SEED true
#define SET_SEED 128434667


// LCG constants for PRNG generator
#define LCG_MULTIPLIER 1103515245
#define LCG_INCREMENT 12345
#define LCG_MODULUS (1U << 31)


#endif