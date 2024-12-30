#include "logger.h"
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>

void log_message(const char* func, const char* format, ...) {
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