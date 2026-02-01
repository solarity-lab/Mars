#include "mlogic.h"

struct Object* ObjectLogicAnd(struct Object* a, struct Object* b) {
    Number_t aval = a->value;
    Number_t bval = b->value;

    return ObjectMakeNumber(aval && bval);
}

struct Object* ObjectLogicOr(struct Object* a, struct Object* b) {
    Number_t aval = a->value;
    Number_t bval = b->value;

    return ObjectMakeNumber(aval || bval);
}

struct Object* ObjectLogicNot(struct Object* a) {
    Number_t aval = a->value;

    return ObjectMakeNumber(!aval);
}