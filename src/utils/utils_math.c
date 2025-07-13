#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L // needed for CLOCK_REALTIME macro from time.h to work
#endif

#include "config.h"
#include "utils_math.h"
#include "utils_log.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


uint32_t seed_generator(bool random_seed){  // local helper function to generate seed for PRNG (if random_seed is true, a seed which is based on current time in nanoseconds is generated)
    if (!random_seed){ 
        return SET_SEED;
    }

    uint32_t time_ns; //time in nanoseconds

    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0) { // get real time
        time_ns = ts.tv_nsec;
    }
    else{ // if getting real time fails, SET_SEED is used as backup
        time_ns = SET_SEED;
        log_error("clock_gettime failed, seed fallback value used: %lld", time_ns);
    }

    return time_ns;
}


// neural network manager functions

float math_sigmoid(float x){ // sigmoid function for neural network nodes 
    return 1.0/(1.0f+expf(-x));
}
float math_sigmoid_derivative(float x){ // sigmoid function derivative
    float s = math_sigmoid(x);
    return s*(1.0f-s);
}
float math_relu(float x){ // relu function for nerual network, returns 0 if x < 0, else returns x
    return x < 0 ? 0.0f : x;
}
float math_relu_derivative(float x){ // relu function derivative
    return x <= 0 ? 0.0f : 1.0f;
}



// random number generator and normalization functions

float math_normalize(uint32_t value, uint32_t normalization_value) { // normalize a value so its between 0.0 and 1.0
    return (float)value / (float)normalization_value;
}


float math_rand_f(bool random_seed){ // generate a random number between 0.0 and 1.0 (if random_seed is true, a random seed will be generated, if false, a set seed is chosen)
    float random_number;
    
    // the seed to start LCG
    uint32_t seed = seed_generator(random_seed);
    
    // Linear Congruential Generator (LCG) constansts
    uint32_t a = LCG_MULTIPLIER;
    uint32_t c = LCG_INCREMENT;
    uint32_t m = LCG_MODULUS;

    seed = (a * seed + c) % m;  // LCG formula
    seed = (a * seed + c) % m;  // LCG formula
    
    random_number = math_normalize(seed, m); // we normalize by m since that's the largest possible number for the seed because of (mod n)

    return random_number;
}

float math_rand_range(float min, float max, bool random_seed){ // return a ranodm float between min and max (if random_seed is true, a random seed will be generated, if false, a set seed is chosen)
    float random_norm_number = math_rand_f(random_seed);
    float range = max - min;
    return min + random_norm_number*range;
}


// vector array operation functions

float math_dot_prod(const float* a, const float* b, int length){ // returns the dotproduct of 2 matricies
    float dot_prod_value = 0;

    for (int i = 0; i < length; i++){ // loops through the length of the vector arrays and multiplies their elements and adds them to dot_prod_value
        dot_prod_value += a[i]*b[i];
    }

    return dot_prod_value;
}

void math_add_arrays(const float* a, const float* b, float* out, int length){ // adds 2 arrays together (each element of each array) in to an out array "out"
    for (int i = 0; i < length; i++){ // loops htrough the length of the arrays and their elements together in the out array "out"
        out[i] = a[i] + b[i];
    }
}

void math_scale_array(float* array, float scalar, int length){ // scales all elements in an array according to the scalar
    for (int i = 0; i < length; i++){ // loops through the length of the array and multiplies the element with the scalar
        array[i] *= scalar;
    }
}



// matrix operation functions

void math_mat_mul(const float* A, const float* B, float* out, int A_rows, int A_cols_B_rows, int B_cols){ // multiplies 2 matricies together in to a pre allocated out matrix "out"
    
    if (A_rows <= 0 || B_cols <= 0 || A_cols_B_rows <= 0) { // matrix validatio
        log_error("Invalid matrix dimensions");
        return;
    }
    for (int i = 0; i < A_rows*B_cols; i++){ // resetting the out matrix
        out[i] = 0.0f;
    }
    
    // matrix multiplication requires a tripple nested for loop, that goes through the length of A's rows and B's columns and multiplies and adds the elements in a specific way
    // A [m x n], B [n x p] and out [m x p]

    for (int row = 0; row < A_rows; row++){ // keeps track of rows, so we calculate each column of row 1 before we move on to the next row.
        // since I guess C doesn't support matricies, the matricies are just 1 dimemsional, and each increment of the size of a row, is a jump to the next row,
        // so each row for a 3x3 matrix begins at 0, 3, and 6. so index 7 for example is row 3, column 2

        for (int col = 0; col < B_cols; col++){ // keeps track of the column

            for (int term = 0; term < A_cols_B_rows; term++){// sums up terms from A and B in a specific way and adds them to the correct place in out

                int idx_out = row * B_cols + col;
                int idx_a   = row * A_cols_B_rows + term;
                int idx_b   = term * B_cols + col;
                out[idx_out] += A[idx_a] * B[idx_b];
            }
        }
    }
}

void math_transpose(const float* in, float* out, int rows_in, int cols_in){ // "rotates" the matrix along its main axis, essentially swaps rows and columns
    if (rows_in <= 0 || cols_in <= 0) { // matrix validation
        log_error("Invalid matrix dimensions");
        return;
    }
    for (int row_T = 0; row_T < cols_in; row_T++){ // Since the "new" matrix will have swapped rows and columns with "old" one, i've decided to make
        // the for loop iterate over the indexes of the "new" matrix, so, row_T represents the row of the transposed matrix, same with col_T
        // and so, vice versa, row_T represents the rows of the old matrix, so i can just use that as a substitute to find the right index on the old matrix

        for (int col_T = 0; col_T < rows_in; col_T++){
            int index_in_matrix = col_T * cols_in + row_T;
            int index_out_matrix = row_T * rows_in + col_T;
            out[index_out_matrix] = in[index_in_matrix];
        }
    }
}
