#ifndef MLABEL_H
#define MLABEL_H

#include "../../Mars/opcode.h"
#include "mars.h"

struct Label {
    address_t address;
    int offset; 
};

struct ProgramLabel {
    struct Label *labels;
    int count;
};

struct ProgramLabel ProgramSetLabel(Instruction *bytecode, MarsSize size);
struct Label ProgramGetLabel(struct ProgramLabel pl, address_t address);

#endif // MLABEL_H