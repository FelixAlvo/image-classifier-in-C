#ifndef FLOAT_TOLERANCE
#define FLOAT_TOLERANCE 0.0001f
#endif

#include "test.h"
#include "utils_log.h"
#include "utils_math.h"
#include "config.h"
#include <math.h>
#include <stdbool.h>


static bool float_equals(float a, float b){ // accounts for floating-point precision errors
    return fabsf(a-b) < FLOAT_TOLERANCE;
}

void test_sigmoid() {
    log_info("Running test_sigmoid...");
    float inputs[] = {-10.0f, -1.0f, 0.0f, 1.0f, 10.0f};
    float expected[] = {
        4.5398e-05f,  // sigmoid(-10)
        0.26894f,     // sigmoid(-1)
        0.5f,         // sigmoid(0)
        0.73106f,     // sigmoid(1)
        0.99995f      // sigmoid(10)
    };
    
    bool passed = true;
    for (int i = 0; i < 5; i++) {
        float result = math_sigmoid(inputs[i]);
        if (!float_equals(result, expected[i])) {
            log_error("sigmoid(%f) = %f, expected %f", inputs[i], result, expected[i]);
            passed = false;
        }
    }
    
    log_test("test_sigmoid", passed);
}



void test_run_test(int test){
    switch (test)
    {
    case TEST_MATH_SIGMOID:
        test_sigmoid();
        break;
    case TEST_MATH_SIGMOID_DERIVATIVE:
        break;
    case TEST_MATH_RELU:
        break;
    case TEST_MATH_RELU_DERIVATIVE:
        break;
    case TEST_MATH_RAND_F:
        break;

    case TEST_MATH_RAND_RANGE:
        break;
    case TEST_MATH_DOT_PROD:
        break;

    case TEST_MATH_ADD_ARRAYS:
        break;
    case TEST_MATH_SCALE_ARRAY:
        break;

    case TEST_MATH_MAT_MUL:
        break;
    case TEST_MATH_TRANSPOSE:
        break;

    
    default:
        break;
    }
}

int main(){
    log_info("\nRunning tests:\n");
    test_run_test(TEST_MATH_SIGMOID);
    return 0;
}