#ifndef FLOAT_TOLERANCE
#define FLOAT_TOLERANCE 0.0001f
#define REGISTER_TEST(fn) {#fn, fn}
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

void test_math_sigmoid() {
    log_info("Running test_math_sigmoid...");
    float inputs[] = {-10.0f, -1.0f, 0.0f, 1.0f, 10.0f};
    float expected[] = {
        4.5398e-05f,
        0.26894f,
        0.5f,
        0.73106f,
        0.99995f  
    };
    
    bool passed = true;
    for (int i = 0; i < 5; i++) {
        float result = math_sigmoid(inputs[i]);
        if (!float_equals(result, expected[i])) {
            log_error("sigmoid(%f) = %f, expected %f", inputs[i], result, expected[i]);
            passed = false;
        }
    }
    
    log_test("test_math_sigmoid", passed);
}

void test_math_sigmoid_derivative(){
    log_info("Running test_math_sigmoid_derivative...");
    float inputs[]   = {-10.0f, -1.0f, 0.0f, 1.0f, 10.0f};
    float expected[] = {4.5395e-05f, 0.19661f, 0.25f, 0.19661f, 4.5395e-05f};
    
    bool passed = true;
    for (int i = 0; i < 5; i++) {
        float result = math_sigmoid_derivative(inputs[i]);
        if (!float_equals(result, expected[i])) {
            log_error("math_sigmoid_derivative(%f) = %f, expected %f", inputs[i], result, expected[i]);
            passed = false;
        }
    }
    
    log_test("test_math_sigmoid_derivative", passed);
}

void test_math_relu(){
    log_info("Running test_math_relu...");
    float inputs[]   = {-10.0f, -1.0f, 0.0f, 1.0f, 10.0f};
    float expected[] = {0.0f, 0.0f, 0.0f, 1.0f, 10.0f};
    
    bool passed = true;
    for (int i = 0; i < 5; i++) {
        float result = math_relu(inputs[i]);
        if (!float_equals(result, expected[i])) {
            log_error("math_relu(%f) = %f, expected %f", inputs[i], result, expected[i]);
            passed = false;
        }
    }
    
    log_test("test_math_relu", passed);
}

void test_math_relu_derivative(){
    log_info("Running test_math_relu_derivative...");
    float inputs[]   = {-10.0f, -1.0f, 0.0f, 1.0f, 10.0f};
    float expected[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f};
    
    bool passed = true;
    for (int i = 0; i < 5; i++) {
        float result = math_relu_derivative(inputs[i]);
        if (!float_equals(result, expected[i])) {
            log_error("math_relu_derivative(%f) = %f, expected %f", inputs[i], result, expected[i]);
            passed = false;
        }
    }
    
    log_test("test_math_relu_derivative", passed);
}

void test_math_normalize() {
    log_info("Running test_math_normalize...");
    uint32_t normalization_value = 1000;

    uint32_t inputs[]   = {0, 100, 250, 500, 750, 1000};
    float expected[]    = {0.0f, 0.1f, 0.25f, 0.5f, 0.75f, 1.0f};

    bool passed = true;
    for (int i = 0; i < 6; i++) {
        float result = math_normalize(inputs[i], normalization_value);
        if (!float_equals(result, expected[i])) {
            log_error("math_normalize(%u, %u) = %f, expected %f",
                      inputs[i], normalization_value, result, expected[i]);
            passed = false;
        }
    }

    log_test("test_math_normalize", passed);
}

void test_math_rand_f_random_seed(){
    log_info("Running test_math_rand_f with a random seed...");
    
    int trials = 1000;
    bool passed = true;
    float min = 1.0f;
    float max = 0.0f;
    
    for (int i = 0; i < trials; i++) {
        float val = math_rand_f(RANDOM_SEED);
        if (val < 0.0f || val > 1.0f) {
            log_error("math_rand_f() out of bounds: %f", val);
            passed = false;
        }
        if (val < min) min = val;
        if (val > max) max = val;
    }
    
    log_test("test_math_rand_f", passed);
}

void test_math_rand_f_set_seed(){
    log_info("Running test_math_rand_f with a set seed...");
    bool passed = true;
    float input = math_rand_f(!RANDOM_SEED);
    float expected = 0.367431;

    passed = float_equals(input, expected);

    log_test("test_math_rand_f", passed);
}

void test_math_rand_f(){
    test_math_rand_f_random_seed();
    test_math_rand_f_set_seed();
}

void test_math_rand_range(){
    log_info("Running test_math_rand_range with a random seed...");
    
    int trials = 10;
    bool passed = true;
    float min = 10.0f;
    float max = 30.0f;
    for (int j = 0; j < 2; j++){
        for (int i = 0; i < trials; i++) {
            float val = math_rand_range(min, max, RANDOM_SEED);
            if (val < min || val > max) {
                log_error("math_rand_range() out of bounds: %f", val);
                passed = false;
            }
        }
        min = -27.0f;
        max = -20.0f;
    }
    log_test("test_math_rand_range", passed);
}

void test_math_dot_prod() {
    log_info("Running test_math_dot_prod...");
    bool passed = true;

    float a1[] = {1, 2, 3};
    float b1[] = {4, 5, 6};
    float expected1 = 32;

    float a2[] = {0, 0, 0};
    float b2[] = {1, 2, 3};
    float expected2 = 0;

    float a3[] = {1, -1, 1};
    float b3[] = {1, 1, 1};
    float expected3 = 1;

    float a4[] = {-1, -2, -3};
    float b4[] = {-4, -5, -6};
    float expected4 = 32;

    float a5[] = {1.5, 2.0, 2.5};
    float b5[] = {2.0, 0.5, 4.0};
    float expected5 = 14;

    struct {
        const float* a;
        const float* b;
        int length;
        float expected;
    } cases[] = {
        {a1, b1, 3, expected1},
        {a2, b2, 3, expected2},
        {a3, b3, 3, expected3},
        {a4, b4, 3, expected4},
        {a5, b5, 3, expected5}
    };

    for (int i = 0; i < 5; i++) {
        float result = math_dot_prod(cases[i].a, cases[i].b, cases[i].length);
        if (!float_equals(result, cases[i].expected)) {
            log_error("dot_prod case %d failed: got %f, expected %f", i + 1, result, cases[i].expected);
            passed = false;
        }
    }

    log_test("test_math_dot_prod", passed);
}

void test_math_add_arrays() {
    log_info("Running test_math_add_arrays...");
    bool passed = true;

    float a1[] = {1, 2, 3};
    float b1[] = {4, 5, 6};
    float expected1[] = {5, 7, 9};

    float a2[] = {0, 0, 0};
    float b2[] = {0, 0, 0};
    float expected2[] = {0, 0, 0};

    float a3[] = {1.5f, 2.5f, 3.5f};
    float b3[] = {0.5f, 0.5f, 0.5f};
    float expected3[] = {2.0f, 3.0f, 4.0f};

    float a4[] = {-1, -2, -3};
    float b4[] = {-4, -5, -6};
    float expected4[] = {-5, -7, -9};

    float a5[] = {100, 200, 300};
    float b5[] = {-100, -200, -300};
    float expected5[] = {0, 0, 0};

    struct {
        const float* a;
        const float* b;
        const float* expected;
        int length;
    } cases[] = {
        {a1, b1, expected1, 3},
        {a2, b2, expected2, 3},
        {a3, b3, expected3, 3},
        {a4, b4, expected4, 3},
        {a5, b5, expected5, 3}
    };

    float out[3];

    for (int i = 0; i < 5; i++) {
        math_add_arrays(cases[i].a, cases[i].b, out, cases[i].length);
        for (int j = 0; j < cases[i].length; j++) {
            if (!float_equals(out[j], cases[i].expected[j])) {
                log_error("add_arrays case %d, index %d: got %f, expected %f",
                          i + 1, j, out[j], cases[i].expected[j]);
                passed = false;
            }
        }
    }

    log_test("test_math_add_arrays", passed);
}

void test_math_scale_array() {
    log_info("Running test_math_scale_array...");
    bool passed = true;

    float a1[] = {1, 2, 3};
    float expected1[] = {2, 4, 6};
    float scale1 = 2.0f;

    float a2[] = {0, 0, 0};
    float expected2[] = {0, 0, 0};
    float scale2 = 5.0f;

    float a3[] = {-1, -2, -3};
    float expected3[] = {-2, -4, -6};
    float scale3 = 2.0f;

    float a4[] = {1.5f, 2.5f, 3.5f};
    float expected4[] = {3.0f, 5.0f, 7.0f};
    float scale4 = 2.0f;

    float a5[] = {100, 200, 300};
    float expected5[] = {10, 20, 30};
    float scale5 = 0.1f;

    struct {
        float* array;
        const float* expected;
        float scalar;
        int length;
    } cases[] = {
        {a1, expected1, scale1, 3},
        {a2, expected2, scale2, 3},
        {a3, expected3, scale3, 3},
        {a4, expected4, scale4, 3},
        {a5, expected5, scale5, 3}
    };

    for (int i = 0; i < 5; i++) {
        math_scale_array(cases[i].array, cases[i].scalar, cases[i].length);
        for (int j = 0; j < cases[i].length; j++) {
            if (!float_equals(cases[i].array[j], cases[i].expected[j])) {
                log_error("scale_array case %d, index %d: got %f, expected %f",
                          i + 1, j, cases[i].array[j], cases[i].expected[j]);
                passed = false;
            }
        }
    }

    log_test("test_math_scale_array", passed);
}

void test_math_mat_mul() {
    log_info("Running test_math_mat_mul...");
    bool passed = true;

    // Case 1: 2x3 * 3x2 => 2x2
    float A1[] = {
        1, 2, 3,
        4, 5, 6
    };
    float B1[] = {
        7, 8,
        9, 10,
        11, 12
    };
    float expected1[] = {
        58, 64,
        139, 154
    };

    // Case 2: 2x2 * 2x2 => 2x2 identity * matrix
    float A2[] = {
        1, 0,
        0, 1
    };
    float B2[] = {
        5, 6,
        7, 8
    };
    float expected2[] = {
        5, 6,
        7, 8
    };

    // Case 3: 1x3 * 3x1 => 1x1 dot product
    float A3[] = {1, 2, 3};
    float B3[] = {4, 5, 6};
    float expected3[] = {32};

    struct {
        const float* A;
        const float* B;
        const float* expected;
        int m, n, p;
    } cases[] = {
        {A1, B1, expected1, 2, 3, 2},
        {A2, B2, expected2, 2, 2, 2},
        {A3, B3, expected3, 1, 3, 1}
    };

    float out[4]; // Max needed size for any test

    for (int c = 0; c < 3; c++) {
        int size = cases[c].m * cases[c].p;

        // Clear `out`
        for (int i = 0; i < size; i++) out[i] = 0.0f;

        math_mat_mul(cases[c].A, cases[c].B, out, cases[c].m, cases[c].n, cases[c].p);

        for (int i = 0; i < size; i++) {
            if (!float_equals(out[i], cases[c].expected[i])) {
                log_error("mat_mul case %d, index %d: got %f, expected %f",
                          c + 1, i, out[i], cases[c].expected[i]);
                passed = false;
            }
        }
    }

    log_test("test_math_mat_mul", passed);
}

void test_math_transpose() {
    log_info("Running test_math_transpose...");
    bool passed = true;

    // Case 1: 2x3 → 3x2
    float A1[] = {
        1, 2, 3,
        4, 5, 6
    };
    float expected1[] = {
        1, 4,
        2, 5,
        3, 6
    };

    // Case 2: 2x2 identity
    float A2[] = {
        1, 0,
        0, 1
    };
    float expected2[] = {
        1, 0,
        0, 1
    };

    // Case 3: 1x3 → 3x1
    float A3[] = {
        7, 8, 9
    };
    float expected3[] = {
        7,
        8,
        9
    };

    struct {
        const float* in;
        const float* expected;
        int rows;
        int cols;
    } cases[] = {
        {A1, expected1, 2, 3},
        {A2, expected2, 2, 2},
        {A3, expected3, 1, 3}
    };

    float out[6]; // large enough for all tests

    for (int c = 0; c < 3; c++) {
        int size = cases[c].rows * cases[c].cols;

        math_transpose(cases[c].in, out, cases[c].rows, cases[c].cols);

        for (int i = 0; i < size; i++) {
            if (!float_equals(out[i], cases[c].expected[i])) {
                log_error("transpose case %d, index %d: got %f, expected %f",
                          c + 1, i, out[i], cases[c].expected[i]);
                passed = false;
            }
        }
    }

    log_test("test_math_transpose", passed);
}

static TestCase test_registry[] = {
    REGISTER_TEST(test_math_sigmoid),
    REGISTER_TEST(test_math_sigmoid_derivative),
    REGISTER_TEST(test_math_relu),
    REGISTER_TEST(test_math_relu_derivative),
    REGISTER_TEST(test_math_normalize),
    REGISTER_TEST(test_math_rand_f),
    REGISTER_TEST(test_math_rand_range),
    REGISTER_TEST(test_math_dot_prod),
    REGISTER_TEST(test_math_add_arrays),
    REGISTER_TEST(test_math_scale_array),
    REGISTER_TEST(test_math_mat_mul),
    REGISTER_TEST(test_math_transpose),
};

void test_run_test(int test_id){

    static const int test_registry_count = sizeof(test_registry) / sizeof(TestCase);

    if (test_id == TEST_ALL) {
        for (int i = 0; i < test_registry_count; i++) {
            test_registry[i].func();
        }
    } else if (test_id >= 1 && test_id <= test_registry_count) {
        test_registry[test_id - 1].func();
    } else {
        log_warn("Unknown test ID: %d", test_id);
    }
}

int main(){
    log_info("\nRunning tests:\n");
    test_run_test(TEST_ALL);
    return 0;
}