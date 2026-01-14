#include "msyntax.h"

enum TOKEN keyword_lookup(const char* ident) {
    for (int i = 0; keywords[i].name != NULL; i++) {
        if (strcmp(ident, keywords[i].name) == 0) return keywords[i].type;
    }
    return T_IDENTIFIER;
}