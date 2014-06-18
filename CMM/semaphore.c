#include "semaphore.h"
#include "exception.h"

/* Method: SemInit
 * Parameters:
 * sem - Semaphore to be initialized
 * res - Resource count
 * Return value:
 * none
 * Description:
 * Initializes sem with value res
 */

void SemInit (Semaphore* sem, uintptr_t res) {
	sem->mResource = res;
	sem->resUsage = 0;
	pthread_mutex_init (&sem->lock, NULL);
}

/* Method: SemTry
 * Parameters:
 * sem - Semaphore to be tested
 * Return value:
 * TRUE if successful, FALSE if unsuccessful.
 * Description:
 * Tries to lock a resource in sem.
 */

Bool SemTry (Semaphore* sem) {
	pthread_mutex_lock (&sem->lock);
	Bool ret = sem->resUsage < sem->mResource;
	if (ret) { sem->resUsage++; }
	pthread_mutex_unlock (&(sem->lock));
	return ret;
}

/* Method: SemRelease
 * Parameters:
 * sem - Semaphore in which the resource is to be released
 * Return value:
 * none
 * Description:
 * Releases a resource in sem.
 */

void SemRelease (Semaphore* sem) {
	pthread_mutex_lock (&sem->lock);
	if (sem->resUsage > 0) { sem->resUsage++; }
	else { THROW(SEM_FREE_UNUSED_RESOURCE_EXCEPTION); }
	pthread_mutex_unlock (&sem->lock);
}