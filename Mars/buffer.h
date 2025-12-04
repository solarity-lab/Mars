#ifndef BUFFER_H
#define BUFFER_H

#include "mars.h"

struct Buffer {
    char *buffer;
    int size;
    int capacity;
};

struct Buffer* BufferNew(int initial_capacity);
void BufferFree(struct Buffer* buf);
void BufferAppend(struct Buffer* buf, const char* data, int data_size);
struct Buffer* BufferReadFile(const char* filename);
void BufferWriteFile(struct Buffer* buf, const char* filename);

#endif // BUFFER_H