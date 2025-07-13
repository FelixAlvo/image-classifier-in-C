#ifndef CONFIG_H
#define CONFIG_H

// seed logic for PRNG generator
#define RANDOM_SEED true
#define SET_SEED 128434667


// LCG constants for PRNG generator
#define LCG_MULTIPLIER 1103515245
#define LCG_INCREMENT 12345;
#define LCG_MODULUS 1U << 31;


#endif