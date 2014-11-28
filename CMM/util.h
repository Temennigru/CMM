#include "bool.h"

/* Method: assertprintf
 * Parameters:
 * asst - Assertion expression result
 * format - Formatable string
 * ... - Format args
 * Return value:
 * none
 * Description:
 * Works similarly to assert, but will print a customized error message and stack trace.
 */

void assertprintf(Bool asst, const char* format, ...);

/* Method: debugprintf
 * Parameters:
 * format - Formatable string
 * ... - Format args
 * Return value:
 * none
 * Description:
 * Works similarly to printf, but will print nothing if compiled with -DNDEBUG flag.
 */

void debugprintf(const char* format, ...);