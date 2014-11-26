#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

/* Method: debugprintf
 * Parameters:
 * format - Formatable string
 * ... - Format args
 * Return value:
 * none
 * Description:
 * Works similarly to printf, but will print nothing if compiled with -DNDEBUG flag.
 */

void debugprintf(const char* format, ...) {
    va_list argptr;
    va_start(argptr, format);
    assert(vfprintf(stdout, format, argptr) >= 0);
    va_end(argptr);
}