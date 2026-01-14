#include "meval.h"

struct Object* __add(struct Object* a, struct Object* b) {
    struct Object* result = ObjectNew();
    result->type = O_NUMBER;
    result->value.f = a->value.f + b->value.f;
    return result;    
}

struct Object* __sub(struct Object* a, struct Object* b) {
    struct Object* result = ObjectNew();
    result->type = O_NUMBER;
    result->value.f = a->value.f - b->value.f;
    return result;    
}

struct Object* __mul(struct Object* a, struct Object* b) {
    struct Object* result = ObjectNew();
    result->type = O_NUMBER;
    result->value.f = a->value.f * b->value.f;
    return result;    
}

struct Object* __div(struct Object* a, struct Object* b) {
    struct Object* result = ObjectNew();
    result->type = O_NUMBER;
    result->value.f = a->value.f / b->value.f;
    return result;    
}

struct Object* __mod(struct Object* a, struct Object* b) {
    struct Object* result = ObjectNew();
    result->type = O_NUMBER;
    result->value.f = (int) a->value.f % (int) b->value.f;
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
    struct Object* a = ProtoStackTake(proto);
    struct Object* b = ProtoStackTake(proto);

    return ObjectAdd(a, b);
}

struct Object* ProtoSub(struct ProtoFormat* proto) {
    struct Object* a = ProtoStackTake(proto);
    struct Object* b = ProtoStackTake(proto);

    return ObjectSub(a, b);    
}

struct Object* ProtoMul(struct ProtoFormat* proto) {
    struct Object* a = ProtoStackTake(proto);
    struct Object* b = ProtoStackTake(proto);

    return ObjectMul(a, b);
}

struct Object* ProtoDiv(struct ProtoFormat* proto) {
    struct Object* a = ProtoStackTake(proto);
    struct Object* b = ProtoStackTake(proto);

    return ObjectDiv(a, b);
}

struct Object* ProtoMod(struct ProtoFormat* proto) {
    struct Object* a = ProtoStackTake(proto);
    struct Object* b = ProtoStackTake(proto);

    return ObjectMod(a, b);    
}