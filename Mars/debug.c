#include "debug.h"

void Debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stdout, "[DEBUG] ");
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");
    va_end(args);
}

void Warning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stdout, "[WARNING] ");
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");
    va_end(args);
}

void Error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[ERROR] ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void FatalWarning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[FATAL WARNING] ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}

void FatalError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[FATAL ERROR] ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
