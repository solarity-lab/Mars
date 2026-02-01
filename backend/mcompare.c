#include "mcompare.h"

struct Object *ObjectCompare(struct Object *a, struct Object *b, Instruction op) {
    int result = __compare(a, b);
    switch (op) {
        case OKGT:
            return ObjectMakeNumber(result > 0);
        case OKGTE:
            return ObjectMakeNumber(result >= 0);
        case OKLT:
            return ObjectMakeNumber(result < 0);
        case OKLTE:
            return ObjectMakeNumber(result <= 0);
        case OKEQ:
            return ObjectMakeNumber(result == 0);
        case OKNEQ:
            return ObjectMakeNumber(result != 0);
    }

    return null_obj;
}

int __compare(struct Object *a, struct Object *b) {
    return (a->value > b->value) - (a->value < b->value);
}

struct ProtoFormat *ProtoCompare(struct ProtoFormat *proto, Instruction op) {
    struct Object *b = ProtoStackTake(proto);
    struct Object *a = ProtoStackTake(proto);

    GCmove(proto->gc, a);
    GCmove(proto->gc, b);
    
    struct Object *result = ObjectCompare(a, b, op);

    ProtoStackPush(proto, result);

    return proto;
}