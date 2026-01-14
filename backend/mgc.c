#include "mgc.h"

struct GarbageCollector* GCNew(void) {
    struct GarbageCollector* gc = malloc(sizeof(struct GarbageCollector));
    gc->p_size = 0;
    gc->p_capacity = 1024;    

    gc->pool = calloc(gc->p_capacity, sizeof(struct Object*));

    return gc;
}

int GCmove(struct GarbageCollector* gc, struct Object* obj) {
    if (gc->p_size >= gc->p_capacity) {
        gc->p_capacity *= 2;
        gc->pool = realloc(gc->pool, gc->p_capacity * sizeof(struct Object*));
    }

    if (obj->ref_count <= 0) {
        gc->pool[gc->p_size++] = obj;
        return GC_SAFE;
    }

    return GC_UNSAFE;
}

int GCSweep(struct GarbageCollector* gc) {
    for (int i = 0; i < gc->p_size; i++) {
        struct Object* obj = gc->pool[i];
        if (obj->ref_count <= 0) {
            ObjectFree(obj);
        }
    }

    gc->p_size = 0;
    return GC_SAFE;
}

int GCStartClean(struct GarbageCollector* gc) {
    if (!gc || !gc->pool) return GC_UNSAFE;

    if (gc->p_size >= GC_MAX) {
        return GCSweep(gc);
    }

    return GC_SAFE;
}