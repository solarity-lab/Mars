#ifndef DEBUG_H
#define DEBUG_H

#include "mars.h"

void Debug(const char* format, ...);
void Error(const char* format, ...);
void Warning(const char* format, ...);
void FatalError(const char* format, ...);
void FatalWarning(const char* format, ...);

#endif // DEBUG_H