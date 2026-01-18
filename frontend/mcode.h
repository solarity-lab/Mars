#ifndef MCODE_H
#define MCODE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define __CODE_ARG_END -1

#include "../../Mars/opcode.h"

struct mcode {
    unsigned char* bytecode;
    int size;
    int index;

    char* file;
};

#define PUSH(c, o) mcode_add_op((c), (o))
#define INSERT(c, o) mcode_insert_code((c), (o))

#define NULL_CODE mcode_new()

struct mcode* mcode_new();

int mcode_free(struct mcode* mcode);
int mcode_add_op(struct mcode* mcode, unsigned char code);
int mcode_insert_code(struct mcode* mcode, struct mcode* mcode2);
int mcode_print(struct mcode* mcode);

int __mcode(struct mcode* mcode, ...);

struct mcode* __mcode_create(int first, ...);

#endif // MCODE
