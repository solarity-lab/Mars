#ifndef MSYNTAX_H
#define MSYNTAX_H

#include "mtoken.h"
#include <string.h>

struct keyword {
    const char* name;
    enum TOKEN type;
};
static struct keyword keywords[] = {
    {"MOVE",     T_MOVE},
    {"CREAT",    T_CREATE},
    {"CLOSE",    T_CLOSE},
    {"TO",       T_TO},
    {"WRITE",    T_WRITE},
    {"READ",     T_READ},
    {"ERASE",    T_ERASE},

    {"PRINT",    T_PRINT},
    {"SCAN",     T_SCAN},

    {"while",    T_WHILE},
    {"if",       T_IF},
    {"then",     T_THEN},
    {"else",     T_ELSE},
    {"break",    T_BREAK},
    {"continue", T_CONTINUE},
    {"do",       T_DO},
    {"end",      T_END},

    {NULL,       T_NONE}
};

enum TOKEN keyword_lookup(const char* ident);

#endif // MSYNTAX_H