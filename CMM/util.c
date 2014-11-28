#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <execinfo.h>
#include <stdlib.h>


void assertprintf(int asst, const char* format, ...) {
    #if defined(NDEBUG) && defined(__GNUC__)
    #else
        if (!asst) {
            va_list argptr;
            size_t size;
            void *buffer[5];
            char **strings;
            size_t i;

            size = backtrace (buffer, 5);
            strings = backtrace_symbols (buffer, size);
            va_start(argptr, format);
            for (i = 0; i < size; ++i) {
                 fprintf(stderr, "%s\n", strings[i]);
             }
            vfprintf(stdout, format, argptr);
            fprintf(stdout, "\n");
            va_end(argptr);
            abort();
        }
    #endif
}


void debugprintf(const char* format, ...) {
    #if defined(NDEBUG) && defined(__GNUC__)
    #else
        va_list argptr;
        va_start(argptr, format);
        vfprintf(stdout, format, argptr);
        va_end(argptr);
    #endif
}

#endif