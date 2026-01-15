#include "mlabel.h"

struct ProgramLabel ProgramSetLabel(Instruction *bytecode, MarsSize size) {
    struct ProgramLabel pl;
    pl.labels = malloc(sizeof(struct Label) * size);
    pl.count = 0;

    for (int i = 0; i < size; i++) {
        if (bytecode[i] == OKADDRESS) {
            if (i + 1 >= size) break;

            pl.labels[pl.count].address = bytecode[i + 1];
            pl.labels[pl.count].offset  = i + 1;
            pl.count++;
            i++;
        }
    }

    return pl;
}

struct Label ProgramGetLabel(struct ProgramLabel pl, address_t address) {
    for (int i = 0; i < pl.count; i++) {
        if (pl.labels[i].address == address) {
            return pl.labels[i];
        }
    }

    return (struct Label){.address = -1, .offset = -1};
}