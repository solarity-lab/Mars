#ifndef MDEBUG_H
#define MDEBUG_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define MARS_BREAK_POINT while (1)

typedef int __err;

#define COMPILER_ERR -1
#define SYNTAX_ERR -2
#define RUNTIME_ERR -3

void error_at(char* fmt, char* file, int line, int row);
void error_type(char* fmt, __err Err);
void error_type_at(char* fmt, __err Err, char* file, int line, int row);

#endif // MDEBUG