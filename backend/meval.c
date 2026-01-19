#include "meval.h"

struct Object* __add(struct Object* a, struct Object* b) {
    struct Object* result = ObjectNew();
    result->type = O_NUMBER;
    result->value = a->value + b->value;
    return result;    
}

struct Object* __sub(struct Object* a, struct Object* b) {
    struct Object* result = ObjectNew();
    result->type = O_NUMBER;
    result->value = a->value - b->value;
    return result;    
}

struct Object* __mul(struct Object* a, struct Object* b) {
    struct Object* result = ObjectNew();
    result->type = O_NUMBER;
    result->value = a->value * b->value;
    return result;    
}

struct Object* __div(struct Object* a, struct Object* b) {
    struct Object* result = ObjectNew();
    result->type = O_NUMBER;
    result->value = a->value / b->value;
    return result;    
}

struct Object* __mod(struct Object* a, struct Object* b) {
    struct Object* result = ObjectNew();
    result->type = O_NUMBER;
    result->value = (int) a->value % (int) b->value;
    return result;    
}

struct Object* ObjectAdd(struct Object* a, struct Object* b) {
    return __add(a, b);    
}

struct Object* ObjectSub(struct Object* a, struct Object* b) {
    return __sub(a, b);
}

struct Object* ObjectMul(struct Object* a, struct Object* b) {
    return __mul(a, b);
}

struct Object* ObjectDiv(struct Object* a, struct Object* b) {
    return __div(a, b);
}

struct Object* ObjectMod(struct Object* a, struct Object* b) {
    return __mod(a, b);    
}

struct Object* ProtoAdd(struct ProtoFormat* proto) {
    struct Object* b = ProtoStackTake(proto);
    struct Object* a = ProtoStackTake(proto);

    GCmove(proto->gc, b);
    GCmove(proto->gc, a);

    struct Object* result = ObjectAdd(a, b);

    ProtoStackPush(proto, result);
}

struct Object* ProtoSub(struct ProtoFormat* proto) {
    struct Object* b = ProtoStackTake(proto);
    struct Object* a = ProtoStackTake(proto);

    GCmove(proto->gc, b);
    GCmove(proto->gc, a);

    struct Object* result = ObjectSub(a, b);

    ProtoStackPush(proto, result);

    return result;
}

struct Object* ProtoMul(struct ProtoFormat* proto) {
    struct Object* b = ProtoStackTake(proto);
    struct Object* a = ProtoStackTake(proto);

    GCmove(proto->gc, b);
    GCmove(proto->gc, a);

    struct Object* result = ObjectMul(a, b);

    ProtoStackPush(proto, result);

    return result;
}

struct Object* ProtoDiv(struct ProtoFormat* proto) {
    struct Object* b = ProtoStackTake(proto);
    struct Object* a = ProtoStackTake(proto);

    GCmove(proto->gc, b);
    GCmove(proto->gc, a);

    struct Object* result = ObjectDiv(a, b);

    ProtoStackPush(proto, result);

    return result;
}

struct Object* ProtoMod(struct ProtoFormat* proto) {
    struct Object* b = ProtoStackTake(proto);
    struct Object* a = ProtoStackTake(proto);

    GCmove(proto->gc, b);
    GCmove(proto->gc, a);

    struct Object* result = ObjectMod(a, b);

    ProtoStackPush(proto, result);

    return result;
}