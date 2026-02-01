#include "mproto.h"

struct ProtoFormat *ProtoNew(void) {
    struct ProtoFormat* proto = malloc(sizeof(struct ProtoFormat));

    proto->para = NULL;
    proto->para_size = 0;
    
    proto->code = NULL;

    proto->g = NULL;
    proto->k = NULL;
    proto->l = NULL;
    proto->s = NULL;
    
    proto->g_size = 0;
    proto->k_size = 0;
    proto->l_size = 0;
    proto->s_size = 0;

    proto->g_capacity = 1024;
    proto->k_capacity = 1024;
    proto->l_capacity = 1024;
    proto->s_capacity = 1024;

    proto->c_size = 0;

    proto->pc = 0;
    proto->prev = NULL;

    proto->labels.count = 0;
    proto->labels.labels = NULL;

    proto->grid = NULL;

    proto->gc = NULL;
    return proto;
}

struct ProtoFormat *ProtoInit(struct ProtoFormat* proto) {
    proto->s = malloc(proto->s_capacity * sizeof(struct Object*));
    proto->k = malloc(proto->k_capacity * sizeof(struct Object*));
    proto->g = malloc(proto->g_capacity * sizeof(struct Object*));
    proto->l = malloc(proto->l_capacity * sizeof(struct Object*));

    proto->gc = GCNew();

    return proto;
}

Flag ProtoStackPush(struct ProtoFormat* proto, struct Object* value) {
    if (proto->s_size == proto->s_capacity) {
        proto->s_capacity *= 2;
        proto->s = realloc(proto->s, proto->s_capacity * sizeof(struct Object*));
        if (!proto->s) return FFALSE;
    }

    INCR_REF(value);
    
    proto->s[proto->s_size++] = value;
    return FTRUE;
}

Flag ProtoStackPop(struct ProtoFormat* proto) {
    struct Object* pop = ProtoStackTake(proto);
    GCmove(proto->gc, pop);
    return 1;
}

struct Object* ProtoStackTake(struct ProtoFormat* proto) {
    struct Object* pop = proto->s[proto->s_size - 1];

    DECR_REF(pop);

    proto->s_size--;
    return pop;
}

struct Object *ProtoStackBack(struct ProtoFormat* proto) {
    if (proto->s_size <= 0) {
        return NULL;
    }
    return proto->s[proto->s_size - 1];
}

struct Object* ProtoLoadGlobal(struct ProtoFormat *proto, address_t address) {
    for (int i = 0; i < proto->g_size; i++) {
        /*
            nếu trùng địa chỉ ảo thì trả về object đó
        */
        if (proto->g[i]->address == address) {
            return proto->g[i];
        }
    }
    // Trả về NULL nếu không thấy
    return NULL;
}

struct Object* ProtoStoreGlobal(struct ProtoFormat *proto, address_t address, struct Object* value, enum ObjectType type) {
    struct Object* object = ProtoLoadGlobal(proto, address);

    if (object) {
        struct Object* old = object->f_value;

        /*
            Giải phóng object cũ trước đó
            bao gồm giảm ref count và move to gc
        */

        if (old) {
            DECR_REF(old);
            GCmove(proto->gc, old);
        }

        // tăng tham chiếu cho object gán
        INCR_REF(value);

        object->type = type;            // định nghĩa lại type (nếu cần)
        object->f_value = value;

        return object;
    }

    if (proto->g_size == proto->g_capacity) {
        proto->g_capacity *= 2;
        proto->g = realloc(proto->g, proto->g_capacity * sizeof(struct Object*));
    }

    struct Object* scope = ObjectNew();

    // tăng tham chiếu cho object gán
    INCR_REF(value);

    scope->address = address;
    scope->type = type;
    scope->f_value = value;

    proto->g[proto->g_size++] = scope;

    return scope;
}

struct Object* ProtoLoadLocal(struct ProtoFormat *proto, address_t address) {
    for (int i = 0; i < proto->l_size; i++) {
        if (proto->l[i]->address == address) {
            return proto->l[i];
        }
    }

    return NULL;
}

struct Object* ProtoStoreLocal(struct ProtoFormat *proto, address_t address, struct Object* value, enum ObjectType type) {
    struct Object* object = ProtoLoadLocal(proto, address);

    if (object) {
        struct Object* old = object->f_value;

        if (old) {
            DECR_REF(old);
            GCmove(proto->gc, old);
        }

        INCR_REF(value);

        object->type = type;
        object->f_value = value;
        return object;
    }

    if (proto->l_size == proto->l_capacity) {
        proto->l_capacity *= 2;
        proto->l = realloc(proto->l, proto->l_capacity * sizeof(struct Object*));
    }

    struct Object* scope = ObjectNew();

    INCR_REF(value);

    scope->address = address;
    scope->type = type;
    scope->f_value = value;

    proto->l[proto->l_size++] = scope;

    return scope;
}

int ProtoPushNum(struct ProtoFormat* proto, Number_t number) {
    struct Object* num = ObjectMakeNumber(number);
    return ProtoStackPush(proto, num);
}