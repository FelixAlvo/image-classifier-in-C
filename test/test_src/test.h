#ifndef TEST_H
#define TEST_H

typedef struct {
    const char* name;
    void (*func)(void);
} TestCase;

void test_run_test(int test);

#endif