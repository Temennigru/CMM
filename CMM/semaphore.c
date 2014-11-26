#include "semaphore.h"
#include "exception.h"

void SemInit (Semaphore* sem, uintptr_t res) {
	sem->mResource = res;
	sem->resUsage = 0;
	pthread_mutex_init (&sem->lock, NULL);
}

Bool SemTry (Semaphore* sem) {
	pthread_mutex_lock (&sem->lock);
	Bool ret = sem->resUsage < sem->mResource;
	if (ret) { sem->resUsage++; }
	pthread_mutex_unlock (&(sem->lock));
	return ret;
}

void SemRelease (Semaphore* sem) {
	pthread_mutex_lock (&sem->lock);
	if (sem->resUsage > 0) { sem->resUsage++; }
	else { THROW(SEM_FREE_UNUSED_RESOURCE_EXCEPTION); }
	pthread_mutex_unlock (&sem->lock);
}