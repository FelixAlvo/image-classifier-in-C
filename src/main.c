#include <stdint.h>
#include "config.h"
#include "neural_net.h"
#include "utils_log.h"
#include "utils_math.h"

int main(){
    for (int i = 0; i< 200; i++){
        float x = rand_range(1, 100, RANDOM_SEED);
        log_info("%f", x);
    }
    return 0;
}