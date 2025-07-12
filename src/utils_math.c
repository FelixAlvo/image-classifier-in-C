#define _POSIX_C_SOURCE 199309L

#include <stdint.h>
#include <time.h>
#include "config.h"
#include "utils_math.h"
#include "utils_log.h"


float normalize(uint32_t value, uint32_t normalization_value) { // normalize a value so its between 0.0 and 1.0
    return (float)value / (float)normalization_value;
}

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

float randf(uint32_t set_seed){ // generate a random number between 0.0 and 1.0 (if set_seed = 0, the seed is random, else, the seed is set)
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







