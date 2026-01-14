#include "menvi.h"
#include "mtool.h"

struct scope* scope_set(int address, char* name) {
    struct scope* scope = malloc(sizeof(struct scope));
    scope->address = address;
    scope->name = strdup(name);

    scope->is_local = 0;
    scope->is_global = 0;
    
    scope->is_closure = 0;
    
    scope->member = NULL;
    scope->prev = NULL;
    return scope;
}

struct menvi* menvi_new(void) {
    struct menvi* menvi = malloc(sizeof(struct menvi));
    menvi->scope_count = 0;
    menvi->scope_max = 1024;
    menvi->scopes = calloc(menvi->scope_max, sizeof(struct scope*));

    menvi->prev = NULL;
    menvi->global = NULL;

    menvi->is_local = 0;
    menvi->is_global = 0;

    menvi->is_function = 0;
    return menvi;
}


struct scope* fine_scope(struct menvi* menvi, char* name) {
    ensure_capacity((void**)&menvi->scopes, &menvi->scope_max, sizeof(struct scope*), menvi->scope_count);

    if (!menvi->scopes) {
        return NULL;
    }

    for (int i = 0; i < menvi->scope_count; i++) {
        struct scope* scope = menvi->scopes[i];

        if (!scope) continue;

        if (strcmp(scope->name, name) == 0) {
            return scope;
        }
    }

    struct menvi *prev = menvi->prev;
    while (prev != NULL && !prev->is_global && prev->is_function) {
        struct scope* found = NULL;
        for (int i = 0; i < prev->scope_count; i++) {
            if (strcmp(prev->scopes[i]->name, name) == 0) {
                found = prev->scopes[i];
                break;
            }
        }

        if (found) {
            found->is_closure = 1;
            return found;
        }

        prev = prev->prev;
    }

    struct menvi* prevl = menvi->prev;
    while (prevl != NULL && !prevl->is_global) {
        struct scope* found = NULL;
        for (int i = 0; i < prevl->scope_count; i++) {
            if (strcmp(prevl->scopes[i]->name, name) == 0) {
                found = prevl->scopes[i];
                break;
            }
        }

        if (found) {
            return found;
        }

        prevl = prevl->prev;
    }

    struct menvi* global = menvi->global;

    if (!global) {
        return NULL;
    }

    for (int i = 0; i < global->scope_count; i++) {
        if (strcmp(global->scopes[i]->name, name) == 0) {
            return global->scopes[i];
        }
    }

    return NULL;
}

struct scope* store_scope(struct menvi* menvi, struct scope* scope) {
    struct scope* existing = fine_scope(menvi, scope->name);
    if (existing != NULL) return existing;

    struct menvi *prev = menvi->prev;

    while (prev != NULL && !prev->is_global) {
        struct scope* found = fine_scope(prev, scope->name); 
        if (found != NULL) {
            found->is_closure = 1;
            return found;
        }
        prev = prev->prev;
    }

    struct menvi* global = menvi->global;
    if (global) { 
        struct scope* found = fine_scope(global, scope->name);
        if (found != NULL) {
            return found;
        }
    }

    ensure_capacity((void**)&menvi->scopes, &menvi->scope_max, sizeof(struct scope*), menvi->scope_count);

    if (menvi->is_local || menvi->is_function) {
        scope->is_local = 1;
    } else {
        scope->is_global = 1;
    }

    menvi->scopes[menvi->scope_count++] = scope;
    return scope;
}