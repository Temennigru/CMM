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

void SemInit (Semaphore* sem, uintptr_t res);
Bool SemTry (Semaphore* sem);
void SemRelease (Semaphore* sem);

#endif