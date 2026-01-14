#ifndef MBUFF_H
#define MBUFF_H

#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct mbuff {
    char *file;
    char *buffer;
    int size;
    char** folders;
    int nf;
    int maxf;

    unsigned char* bytecode;
    int bytecode_size;
};

struct mbuff*
mbuff_new(void);

int
mbuff_free
(struct mbuff *zio);

struct mbuff*
mbuff_read_file
(char* file);

#endif // MBUFF_H