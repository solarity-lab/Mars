#include "mcompare.h"

struct Object *ObjectCompare(struct Object *a, struct Object *b, Instruction op) {
    int result = __compare(a, b);
    switch (op) {
        case OKGT:
            return ObjectMakeFloat(result > 0);
        case OKGTE:
            return ObjectMakeFloat(result >= 0);
        case OKLT:
            return ObjectMakeFloat(result < 0);
        case OKLTE:
            return ObjectMakeFloat(result <= 0);
        case OKEQ:
            return ObjectMakeFloat(result == 0);
        case OKNEQ:
            return ObjectMakeFloat(result != 0);
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