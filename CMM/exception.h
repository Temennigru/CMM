#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include "bool.h"
#include <setjmp.h>

jmp_buf ex_buf__; // Global variable to define the jump. If it is local it won't work.
int ex_code__; // Exception code. It is set during throw and is used when longjmp fails.
extern Bool was_try__; // For checking for errors.

/* TRY CATCH block still doesn't handle signals. Use with care. */

#define TRY do{ Bool temp_was_try__ = was_try__; was_try__ = TRUE; jmp_buf temp_ex_buf__ = ex_buf__; switch( (exc_code__ = setjmp(ex_buf__)) ){ case 0:
#define FINALLY break; default:
#define CATCH(x) break; case x:
#define ETRY } ex_buf__ = temp_ex_buf__; was_try__ = temp_was_try__ }while(0)
#define THROW(x) ex_code__ = x; longjmpthrow(ex_buf__, x)

#define GENERIC_EXCEPTION (1)
#define INDEX_OUT_OF_RANGE_EXCEPTION (2)
#define CONTAINER_EMPTY_EXCEPTION (3)
#define MATRIX_RESIZE_NOT_GREATER (4)
#define NEGATIVE_INDEX_OR_SIZE (5)
#define INVALID_METHOD_MODE (6)
#define FILE_NOT_OPEN_EXCEPTION (7)
#define NOT_ENOUGH_MEMORY_EXCEPTION (8)
#define SEM_FREE_UNUSED_RESOURCE_EXCEPTION (9)
#define SIGHUP_EXCEPTION (10)
#define SIGINT_EXCEPTION (11)
#define SIGILL_EXCEPTION (12)
#define SIGABRT_EXCEPTION (13)
#define SIGFPE_EXCEPTION (14)
#define SIGBUS_EXCEPTION (15)
#define SIGSEGV_EXCEPTION (16)
#define SIGSYS_EXCEPTION (17)
#define SIGTERM_EXCEPTION (18)

extern const char* _ErrorMessage[]; // Error message array

/* How to use:
 * THROW([Exception enum]) - Trows an exception with the colde
 * Ex: TROW(SIGBUS_EXCEPTION);
 *
 * TRY/CATCH([Exception enum]) - Catches exceptions
 * Ex: TRY
 *         foo;
 *     CATCH(GENERIC_EXCEPTION)
 *         bar;
 *     ETRY;
 *
 * FINALLY - Differently from most OOPLs, finally in CMM catches previously uncaught exceptions.
 * Ex: TRY
 *         foo;
 *     CATCH(INDEX_OUT_OF_RANGE_EXCEPTION)
 *         "caught index out of range exception";
 *     FINALLY
 *         "caught some other exception"
 *     ETRY;
 *
 */


#endif
