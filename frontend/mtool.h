#ifndef MTOOL_H
#define MTOOL_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

char* Mstrndup(const char* src, int n);

void ensure_capacity(void **mem, int *size, int elem_size, int index);

char* __Mstring(const char* fmt, ...);

#endif // MTOOL