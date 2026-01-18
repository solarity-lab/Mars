#include "mtool.h"

char* Mstrndup(const char* src, int n) {
    char* dst = malloc(n + 1);
    if (!dst) return NULL;

    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
    dst[n] = '\0';

    return dst;
}

void ensure_capacity(void **mem, int *size, int elem_size, int index) {
    if (index >= *size) {
        *size *= 2;
        void *tmp = realloc(*mem, (*size) * elem_size);
        if (!tmp) exit(1);
        *mem = tmp;
    }
}

void clear(void) {
    printf("\033[H\033[2J");
    fflush(stdout);
}

char* __Mstring(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    va_list args_copy;
    va_copy(args_copy, args);
    int len = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);

    if (len < 0) {
        va_end(args);
        return NULL;
    }

    char* buf = (char*)malloc(len + 1);
    if (!buf) {
        va_end(args);
        return NULL;
    }

    vsnprintf(buf, len + 1, fmt, args);
    va_end(args);

    return buf;
}