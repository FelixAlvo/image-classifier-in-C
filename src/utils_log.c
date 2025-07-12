#include <stdio.h>
#include <stdarg.h>
#include "config.h"

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

void log_set_logfile(const char* filepath){
    
}