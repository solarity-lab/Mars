#include "mdebug.h"

void error_at(char* fmt, char* file, int line, int row) {
    printf("%s at file %s:%d:%d\n", fmt, file, line, row);
    MARS_BREAK_POINT;
    return;
}

void error_type(char* fmt, __err Err) {
    printf("%s %d\n", fmt, Err);
    MARS_BREAK_POINT;
    return;
}

void error_type_at(char* fmt, __err Err, char* file, int line, int row) {
    printf("%d: %s at file %s:%d:%d\n", Err, fmt, file, line, row);
    MARS_BREAK_POINT;
    return;
}
