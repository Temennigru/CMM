#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

void debugprintf(const char* format, ...) {
    va_list argptr;
    va_start(argptr, format);
    assert(vfprintf(stdout, format, argptr) >= 0);
    va_end(argptr);
}

#endif