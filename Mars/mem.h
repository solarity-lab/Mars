#ifndef MEM_H
#define MEM_H

#include "mars.h"
#include "debug.h"

void* _Mmalloc(size_t size);
void  _Mfree(void* ptr);
void* _Mrealloc(void* ptr, size_t new_size);
void* _Mcalloc(size_t num, size_t size);

void* _Mmalloc_raw(size_t size);
void  _Mfree_raw(void* ptr);
void* _Mrealloc_raw(void* ptr, size_t new_size);
void* _Mcalloc_raw(size_t num, size_t size);

#endif // MEM_H