#ifndef CONFIG_H
#define CONFIG_H

// loop exit condition
#define LOOP_MAX_ITERATIONS 20

// test function macros
#define TEST_ALL 0

#define TEST_MATH_SIGMOID 1
#define TEST_MATH_SIGMOID_DERIVATIVE 2
#define TEST_MATH_RELU 3
#define TEST_MATH_RELU_DERIVATIVE 4

#define TEST_MATH_RAND_F 101
#define TEST_MATH_RAND_RANGE 102
#define TEST_MATH_NORMALIZE 103

#define TEST_MATH_DOT_PROD 201
#define TEST_MATH_ADD_ARRAYS 202
#define TEST_MATH_SCALE_ARRAY 203

#define TEST_MATH_MAT_MUL 301
#define TEST_MATH_TRANSPOSE 302

// seed logic for PRNG generator
#define RANDOM_SEED true
#define SET_SEED 128434667


// LCG constants for PRNG generator
#define LCG_MULTIPLIER 1103515245
#define LCG_INCREMENT 12345
#define LCG_MODULUS (1U << 31)

// Image-handler

#define MAGIC_NUMBER_P2 "P2"


#endif