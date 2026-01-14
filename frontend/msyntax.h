#ifndef MSYNTAX_H
#define MSYNTAX_H

#include "mtoken.h"
#include <string.h>

struct keyword {
    const char* name;
    enum TOKEN type;
};
static struct keyword keywords[] = {
    {"SELECT",   T_SELECT},
    {"FROM",     T_FROM},
    {"WHERE",    T_WHERE},
    {"EXPORT",   T_EXPORT},
    {"PARSE",    T_PARSE},
    {"IMPORT",   T_IMPORT},
    {"TABLE",    T_TABLE},
    {"CREATE",   T_CREAT},
    {"MULTI",    T_MULTI},
    {"PRINT",    T_PRINT},
    {"SCAN",     T_SCAN},

    {"while",    T_WHILE},
    {"if",       T_IF},
    {"then",     T_THEN},
    {"else",     T_ELSE},
    {"for",      T_FOR},
    {"in",       T_IN},
    {"break",    T_BREAK},
    {"continue", T_CONTINUE},
    {"do",       T_DO},
    {"end",      T_END},
    {"let",      T_LET},
    {"function", T_FUNC},
    {"return",   T_RETURN},
    {"true",     T_TRUE},
    {"false",    T_FALSE},
    {"and",      T_AND},
    {"or",       T_OR},
    {"not",      T_NOT},
    {NULL,       T_NONE}
};

enum TOKEN keyword_lookup(const char* ident);

#endif // MSYNTAX_H