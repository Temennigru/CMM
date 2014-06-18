#ifndef _FIFO_H
#define _FIFO_H

#include "bool.h"
#include <stdlib.h>

typedef struct _Fifo {
	uintptr_t size;
	uintptr_t mSize; // Max size
	void** elementArray;
	uintptr_t first, last; // Pointer to first and last elements
}Fifo;

void FifoInit (Fifo* fifo);
void FifoDelete (Fifo* fifo);
void FifoPush (Fifo* fifo, void* element);
void* FifoPop (Fifo* fifo);
Bool FifoIsEmpty (Fifo* fifo);
uintptr_t FifoSize (Fifo* fifo);

#endif
