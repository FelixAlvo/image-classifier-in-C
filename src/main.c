#include "neural_net.h"
#include "config.h"
#include "utils_log.h"
#include "utils_math.h"
#include "image_loader.h"
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

int main(){
    Image* image = il_load_pgm("images/apollonian_gasket.ascii.pgm");
    il_free_image(image);
    return 0;
}