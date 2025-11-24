#include "code.h"

struct Code*
CodeNew(void) {
    struct Code* code = (struct Code*) malloc(sizeof(struct Code));

    code->size = 0;
    code->capacity = 1024;
    code->code = malloc(sizeof(byte) * code->capacity);
    
    return code;
}

int
CodeFree
(struct Code* code) {
    free(code);
    return 0;
}

void
CodeAdd
(struct Code* code, byte op) {
    if  (code->size >= code->capacity) {
        code->capacity *= 2;
        code->code = realloc(code->code, sizeof(byte) * code->capacity);
    }

    code->code[code->size++] = op;
}

void
CodePrint
(struct Code* code) {
    return;
}
