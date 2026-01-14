#include "mobj.h"

struct Object* ObjectNew(void) {
    struct Object* object = malloc(sizeof(struct Object));
    object->ref_count = 0;
    object->address = 0;
    object->f_value = NULL;
    object->is_closure = 0;
    object->is_return = 0;
    object->type = O_NULL;
    return object;
}

int ObjectFree(struct Object* object) {
    free(object);
    return 0;
}

struct Object* ObjectMakeFloat(float f) {
    struct Object* object = ObjectNew();
    object->type = O_NUMBER;
    object->value.f = f;
    return object;
}

struct Object* ObjectMakeBool(int _b) {
    struct Object* object = ObjectNew();
    object->type = O_BOOL;
    object->value._b = _b;
    return object;
}

struct Object* ObjectMakeLong(long l) {
    struct Object* object = ObjectNew();
    object->type = O_NUMBER;
    object->value.l = l;
    return object;
}