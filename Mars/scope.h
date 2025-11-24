#ifndef SCOPE_H
#define SCOPE_H

#include <stdlib.h>
#include <string.h>
#include "tool.h"

#define NOT_FOUND -999

struct Scope {
    int address;
    char* name;
};

struct Environment {
    struct Scope** table;
    int size;
    int capacity; 

    int is_local;
    struct Scope *function; // point to function table
    
    struct Scope** previous;
};

struct Scope*
ScopeNew(void);

struct Environment* 
EnvironmentNew(void);

struct Scope* ScopeSet
(int address, char* name);

struct Scope*
EnvironmentStoreScope
(struct Environment *envi, int address, char* name);

struct Scope*
EnvironmentGetScope
(struct Environment *envi, char* name);

#endif // SCOPE_H
