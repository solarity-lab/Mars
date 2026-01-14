#ifndef MEVAL_H
#define MEVAL_H

#include "mobj.h"
#include "mproto.h"
#include "mars.h"

struct Object* __add(struct Object* a, struct Object* b);
struct Object* __sub(struct Object* a, struct Object* b);
struct Object* __mul(struct Object* a, struct Object* b);
struct Object* __div(struct Object* a, struct Object* b);
struct Object* __mod(struct Object* a, struct Object* b);

struct Object* ObjectAdd(struct Object* a, struct Object* b);
struct Object* ObjectSub(struct Object* a, struct Object* b);
struct Object* ObjectMul(struct Object* a, struct Object* b);
struct Object* ObjectDiv(struct Object* a, struct Object* b);
struct Object* ObjectMod(struct Object* a, struct Object* b);

struct Object* ProtoAdd(struct ProtoFormat* proto);
struct Object* ProtoSub(struct ProtoFormat* proto);
struct Object* ProtoMul(struct ProtoFormat* proto);
struct Object* ProtoDiv(struct ProtoFormat* proto);
struct Object* ProtoMod(struct ProtoFormat* proto);

#endif // MEVAL_H