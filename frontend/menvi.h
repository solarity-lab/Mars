#ifndef MENVI_H
#define MENVI_H

#include <stdlib.h>
#include <string.h>

struct scope {
    int address;
    char* name;
    
    int is_local;
    int is_global;
    int is_closure;

    struct scope** member;
    struct scope* prev;
};

struct menvi {
    struct scope** scopes;
    int scope_count;
    int scope_max;

    struct menvi* prev;
    struct menvi* global;

    int is_local;
    int is_global;
    int is_function;
};

struct scope* scope_set(int address, char* name);
struct menvi* menvi_new(void);

struct scope* fine_scope(struct menvi* menvi, char* name);
struct scope* store_scope(struct menvi* menvi, struct scope* scope);

#endif // MENVI_H
