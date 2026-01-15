#ifndef MCOMPARE_H
#define MCOMPARE_H

#include "mobj.h"
#include "mproto.h"

#define OP_GT 0
#define OP_GTE 1
#define OP_LT 2
#define OP_LTE 3
#define OP_EQ 4
#define OP_NEQ 5

struct Object *ObjectCompare(struct Object *a, struct Object *b, Instruction op);

int __compare(struct Object *a, struct Object *b);

struct ProtoFormat *ProtoCompare(struct ProtoFormat *proto, Instruction op);

#endif // MCOMPARE_H