#include "mcode.h"

struct mcode* mcode_new() {
    struct mcode* mcode = (struct mcode*) malloc(sizeof(struct mcode));

    mcode->bytecode = (unsigned char*) malloc(1024 * sizeof(unsigned char));
    mcode->size = 1024;
    mcode->index = 0;
    mcode->file = NULL;
    return mcode;
}

int mcode_free(struct mcode* mcode) {
    if (!mcode) return 0;
    free(mcode->bytecode);
    free(mcode);
    return 0;
}

int mcode_add_op(struct mcode* mcode, unsigned char code) {
    if (mcode->index >= mcode->size) {
        mcode->size *= 2;
        mcode->bytecode = (unsigned char*)realloc(mcode->bytecode, mcode->size);
    }

    mcode->bytecode[mcode->index++] = code;
    return 0;
}

int mcode_insert_code(struct mcode* mcode, struct mcode* mcode2) {
    for (int i = 0; i < mcode2->index; i++) {
        mcode_add_op(mcode, mcode2->bytecode[i]);
    }
    return 0;
}

int mcode_print(struct mcode* mcode) {
    if (!mcode || !mcode->bytecode) {
        printf("mcode is NULL\n");
        return -1;
    }

    printf("== BYTECODE ==\n");

    int i = 0;
    while (i < mcode->index) {
        unsigned char op = mcode->bytecode[i++];

        printf("[%04d] 0x%02X  ", i - 1, op);

        switch (op) {
            case OKADD:  printf("ADD\n"); break;
            case OKSUB:  printf("SUB\n"); break;
            case OKMUL:  printf("MUL\n"); break;
            case OKDIV:  printf("DIV\n"); break;
            case OKHALT: printf("HALT\n"); break;
            case OKPOP:  printf("POP\n"); break;
            case OKCALL: printf("CALL\n"); break;

            case OKJMP: {
                unsigned char addr = mcode->bytecode[i++];
                printf("JMP %d\n", addr);
                break;
            }

            case OKJMP_IF_FALSE: {
                unsigned char addr = mcode->bytecode[i++];
                printf("JMP_IF_FALSE %d\n", addr);
                break;
            }

            case OKADDRESS: {
                unsigned char addr = mcode->bytecode[i++];
                printf("ADDRESS %d\n", addr);
                break;
            }

            case OKMAKE_ARGS: {
                unsigned char addr = mcode->bytecode[i++];
                printf("MAKEARGS %d\n", addr);
                break;
            }

            case OKMAKEFUNC: {
                unsigned char addr = mcode->bytecode[i++];
                printf("MAKEFUNC %d\n", addr);
                break;
            }

            case OKMAKE_CLOSURE: {
                unsigned char addr = mcode->bytecode[i++];
                printf("MAKECLOSURE %d\n", addr);
                break;
            }

            case OKLOAD_CLOSURE: {
                unsigned char addr = mcode->bytecode[i++];
                printf("LOADCLOSURE %d\n", addr);
                break;
            }

            case OKLOAD_LOCAL: {
                unsigned char addr = mcode->bytecode[i++];
                printf("LOADLOCAL %d\n", addr);
                break;
            }

            case OKSTORE_LOCAL: {
                unsigned char addr = mcode->bytecode[i++];
                printf("STORELOCAL %d\n", addr);
                break;
            }

            case OKSTORE_CLOSURE: {
                unsigned char addr = mcode->bytecode[i++];
                printf("STORECLOSURE %d\n", addr);
                break;
            }

            case OKPUSH_NUM: {
                float value;
                memcpy(&value, &mcode->bytecode[i], sizeof(float));
                i += 4;
                printf("PUSH_NUM %g\n", value);
                break;
            }

            case OKPUSH_BOOL: {
                unsigned char b = mcode->bytecode[i++];
                printf("PUSH_BOOL %d\n", b);
                break;
            }

            case OKLOAD: {
                unsigned char addr = mcode->bytecode[i++];
                printf("LOAD %d\n", addr);
                break;
            }

            case OKSTORE: {
                unsigned char addr = mcode->bytecode[i++];
                printf("STORE %d\n", addr);
                break;
            }

            case OKRETURN: printf("RETURN\n"); break;
            case OKSTART_FUNC: printf("START_FUNC\n"); break;
            case OKEND_FUNC: printf("END_FUNC\n"); break;
            case OKEND_CLOSURE: printf("END_CLOSURE\n"); break;
            case OKEQ:  printf("EQ\n"); break;
            case OKNEQ: printf("NEQ\n"); break;
            case OKLT:  printf("LT\n"); break;
            case OKLTE: printf("LTE\n"); break;
            case OKGT:  printf("GT\n"); break;
            case OKGTE: printf("GTE\n"); break;
            case OKPRINT: printf("PRINT\n"); break;

            default:
                printf("UNKNOWN\n");
                break;
        }
    }

    return 0;
}

int __mcode(struct mcode* mcode, ...) {
    if (!mcode) return -1;

    va_list args;
    va_start(args, mcode);

    int op;
    int count = 0;

    while ((op = va_arg(args, int)) != -1) {
        if (mcode_add_op(mcode, (unsigned char)op) != 0) {
            va_end(args);
            return -1;
        }
        count++;
    }

    va_end(args);
    return count;
}