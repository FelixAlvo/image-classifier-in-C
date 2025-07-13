#include "config.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

void log_info(const char* fmt, ...){
    // starts variadic variable because we can have many args in the log functions
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}

void log_warn(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    printf("\n");
    va_end(args);
}

void log_error(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    printf("\n");
    va_end(args);
}

void log_test(const char* label, bool passed) {
    if (passed) {
        printf("[\033[1;34mPASS\033[0m] %s\n", label);  // blue
    } else {
        printf("[\033[1;31mFAIL\033[0m] %s\n", label);  // red
    }
}

void log_set_logfile(const char* filepath){
    (void)filepath; // suppress unused warning
    log_warn("log_set_logfile is not implemented.");
}