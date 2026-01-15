#ifndef MVM_H
#define MVM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mproto.h"
#include "mobj.h"
#include "meval.h"
#include "mcompare.h"

#include "../../Mars/opcode.h"

struct ProtoFormat* ProtoRunCode(struct ProtoFormat* proto, Instruction *bytecode, MarsSize size);

#endif // MVM_H