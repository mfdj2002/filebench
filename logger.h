// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>

// Define the function as static inline to avoid linking issues
static inline void log_message(const char* func, const char* format, ...) {
    time_t now;
    struct tm* tm_info;
    struct timespec ts;
    char timestamp[32];
    
    clock_gettime(CLOCK_REALTIME, &ts);
    now = time(NULL);
    tm_info = localtime(&now);
    
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    
    pthread_t tid = pthread_self();
    
    printf("%s.%06ld [%lu] %s: ", 
           timestamp, 
           ts.tv_nsec / 1000, 
           (unsigned long)tid,
           func);
    
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    
    printf("\n");
}

#define LOG(...) log_message(__func__, __VA_ARGS__)

#endif // LOGGER_H