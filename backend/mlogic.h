#ifndef MLOGIC_H
#define MLOGIC_H

#include "mobj.h"
#include "mproto.h"
#include "mars.h"

struct Object* ObjectLogicAnd(struct Object* a, struct Object* b);
struct Object* ObjectLogicOr(struct Object* a, struct Object* b);
struct Object* ObjectLogicNot(struct Object* a);

#endif