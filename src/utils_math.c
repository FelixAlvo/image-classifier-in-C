#define _POSIX_C_SOURCE 199309L

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "config.h"
#include "utils_math.h"
#include "utils_log.h"


uint32_t seed_generator(uint32_t set_seed){  // local helper function to generate seed for PRNG (if set_seed is 0, random seed is used based on current time in nanoseconds)
    if (set_seed != 0){
        return set_seed;
    }

    uint32_t time_ns; //time in nanoseconds

    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0) { // get real time
        time_ns = ts.tv_nsec;
    }
    else{
        time_ns = set_seed;
        log_error("clock_gettime failed, seed fallback value used: %lld", time_ns);
    }

    return time_ns;
}

float sigmoid(float x){ // sigmoid function for neural network nodes 
    return 1.0/(1.0f+expf(-x));
}
float sigmoid_derivative(float x){ // sigmoid function derivative
    float s = sigmoid(x);
    return s*(1.0f-s);
}
float relu(float x){ // relu function for nerual network, returns 0 if x < 0, else returns x
    return x < 0 ? 0.0f : x;
}
float relu_derivative(float x){
    return x < 0 ? 0.0f : 1.0f;
}



float normalize(uint32_t value, uint32_t normalization_value) { // normalize a value so its between 0.0 and 1.0
    return (float)value / (float)normalization_value;
}


float rand_f(uint32_t set_seed){ // generate a random number between 0.0 and 1.0 (if set_seed = 0, the seed is random, else, the seed is set)
    float random_number;
    
    // the seed to start LCG
    uint32_t seed = seed_generator(set_seed);
    
    // Linear Congruential Generator (LCG) constansts
    // multiplier
    uint32_t a = 1103515245;
    // increment
    uint32_t c = 12345;
    // modulus
    uint32_t m = 1U << 31;

    seed = (a * seed + c) % m;  // LCG formula
    
    random_number = normalize(seed, m); // we normalize by m since that's the largest possible number for the seed because of (mod n)

    return random_number;
}

float rand_range(float min, float max, uint32_t set_seed){ // return a ranodm float between min and max (if set_seed == 0 then random seed is used, else, set seed is used)
    float random_norm_number = rand_f(set_seed);
    float range = max - min;
    return min + random_norm_number*range;
}

