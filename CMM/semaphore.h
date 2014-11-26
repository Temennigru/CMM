#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <stdlib.h>
#include <pthread.h>
#include "Bool.h"

typedef struct _Sem {
	pthread_mutex_t lock;
	uintptr_t mResource;
	uintptr_t resUsage;
} Semaphore;

/* Method: SemInit
 * Parameters:
 * sem - Semaphore to be initialized
 * res - Resource count
 * Return value:
 * none
 * Description:
 * Initializes sem with value res
 */

void SemInit (Semaphore* sem, uintptr_t res);

/* Method: SemTry
 * Parameters:
 * sem - Semaphore to be tested
 * Return value:
 * TRUE if successful, FALSE if unsuccessful.
 * Description:
 * Tries to lock a resource in sem.
 */

Bool SemTry (Semaphore* sem);

/* Method: SemRelease
 * Parameters:
 * sem - Semaphore in which the resource is to be released
 * Return value:
 * none
 * Description:
 * Releases a resource in sem.
 */

void SemRelease (Semaphore* sem);

#endif