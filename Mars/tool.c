#include "tool.h"

char* _Mstrdup(char* s) {
    int len = 0;
    while (s[len]) len++;

    char* dup = (char*) malloc(len + 1);

    int i = 0;
    while (i < len) {
        dup[i] = s[i];
        i++;
    }
    dup[i] = 0;

    return dup;
}
