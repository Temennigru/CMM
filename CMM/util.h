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