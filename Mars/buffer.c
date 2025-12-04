#include "buffer.h"

struct Buffer* BufferNew(int initial_capacity) {
    struct Buffer* buf = (struct Buffer*) malloc(sizeof(struct Buffer));
    buf->size = 0;
    buf->capacity = initial_capacity;
    buf->buffer = (char*) malloc(sizeof(char) * buf->capacity);
    return buf;
}

void BufferFree(struct Buffer* buf) {
    free(buf->buffer);
    free(buf);
}

void BufferAppend(struct Buffer* buf, const char* data, int data_size) {
    while (buf->size + data_size > buf->capacity) {
        buf->capacity *= 2;
        buf->buffer = realloc(buf->buffer, sizeof(char) * buf->capacity);
    }
    for (int i = 0; i < data_size; i++) {
        buf->buffer[buf->size++] = data[i];
    }
}

struct Buffer* BufferReadFile(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    struct Buffer* buf = BufferNew((int)size);
    buf->size = fread(buf->buffer, 1, size, f);
    fclose(f);
    return buf;
}

void BufferWriteFile(struct Buffer* buf, const char* filename) {
    if (!buf) return;

    FILE* f = fopen(filename, "wb");
    if (!f) {
        perror("Cannot open file for writing");
        return;
    }
    fwrite(buf->buffer, 1, buf->size, f);
    fclose(f);
}