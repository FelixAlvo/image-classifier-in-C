#ifndef UTILS_LOG_H
#define UTILS_LOG_H

void log_info(const char* fmt, ...);
void log_warn(const char* fmt, ...);
void log_error(const char* fmt, ...);
void log_set_logfile(const char* filepath);

#endif
