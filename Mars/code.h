#ifndef CODE_H
#define CODE_H

#include <stdlib.h>

#define OP_PUSH '\x01'
#define OP_POP '\x02'
#define OP_PRINT '\x03'

#define OP_ADD '\x04'
#define OP_SUB '\x05'
#define OP_DIV '\x06'
#define OP_MUL '\x07'

#define OP_START '\x08'
#define OP_END '\x09'

typedef unsigned char byte;

struct Code {
    byte* code;
    int size;
    int capacity;
};

struct Code*
CodeNew(void);

int
CodeFree
(struct Code* code);

void
CodeAdd
(struct Code* code, byte op);

void
CodePrint
(struct Code* code);

#endif // CODE_H
