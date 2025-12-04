#include "mem.h"

void* _Mmalloc(size_t size) {
    void* ptr = _Mmalloc_raw(size);
    if (!ptr) FatalError("Memory allocation failed for size %zu bytes", size);
    memset(ptr, 0, size);
    return ptr;
}

void _Mfree(void* ptr) {
    if (ptr) _Mfree_raw(ptr);
}

void* _Mrealloc(void* ptr, size_t new_size) {
    void* new_ptr = _Mrealloc_raw(ptr, new_size);
    if (!new_ptr) FatalError("Memory reallocation failed for size %zu bytes", new_size);
    return new_ptr;
}

void* _Mcalloc(size_t num, size_t size) {
    void* ptr = _Mcalloc_raw(num, size);
    if (!ptr) FatalError("Memory allocation failed for %zu elements of size %zu bytes", num, size);
    return ptr;
}

void* _Mmalloc_raw(size_t size) {
    return malloc(size);
}

void _Mfree_raw(void* ptr) {
    if (ptr) free(ptr);
}

void* _Mrealloc_raw(void* ptr, size_t new_size) {
    return realloc(ptr, new_size);
}

void* _Mcalloc_raw(size_t num, size_t size) {
    return calloc(num, size);
}
