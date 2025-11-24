#include "scope.h"

struct Scope*
ScopeNew(void) {
   struct Scope* scope = (struct Scope*) malloc(sizeof(struct Scope));

   scope->address = 0;
   scope->name = NULL;

   return scope;
}

struct Environment*
EnvironmentNew(void) {
    struct Environment *envi = (struct Environment*) malloc(sizeof(struct Environment));
    
    envi->size = 0;
    envi->capacity = 1024;
    envi->table = (struct Scope**) calloc(envi->capacity, sizeof(struct Scope*));

    envi->is_local = 0;
    envi->function = NULL;
    envi->previous = NULL;

    return envi;
}

struct Scope*
ScopeSet
(int address, char* name) {
    struct Scope* scope = ScopeNew();
    scope->address = address;
    scope->name = _Mstrdup(name);

    return scope;
}

struct Scope*
EnvironmentStoreScope
(struct Environment *envi, int address, char* name) {
    if (envi->size >= envi->capacity) {
        envi->capacity *= 2;
        envi->table = realloc(envi->table, envi->capacity * sizeof(struct Scope*));
    }

    for (int i = 0; i < envi->size; i++) {
        struct Scope *scope = envi->table[i];
        if (scope->address == address) {
            return scope;
        }
    }

    struct Scope* scope = ScopeSet(address, name);
    
    envi->table[envi->size++] = scope;
    return scope;
}

struct Scope*
EnvironmentGetScope
(struct Environment *envi, char* name) {
    for (int i = 0; i < envi->size; i++) {
        struct Scope *scope = envi->table[i];
        if (strcmp(scope->name, name) == 0) {
            return scope;
        }
    }
    
    return NULL;
}
