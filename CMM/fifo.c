#include "fifo.h"
#include "bool.h"
#include "exception.h"
#include <stdlib.h>

void FifoInit (Fifo* fifo) {
	fifo->mSize = 100;
	fifo->size = 0;
	fifo->first = 0;
	fifo->last = 0;
	fifo->elementArray = (void**) malloc (100 * sizeof (void*) );	
}

void FifoDelete (Fifo* fifo) {
	fifo->mSize = 0;
	fifo->size = 0;
	fifo->first = 0;
	fifo->last = 0;
	free (fifo->elementArray);
	fifo->elementArray = NULL; // To prevent another "delete then access" problem
}

void FifoPush (Fifo* fifo, void* element) {
	if (fifo->size == fifo->mSize) {
		void** temp = (void**) malloc ( (2*fifo->mSize) * sizeof (void*) );
		unsigned long i, j = 0;
		// Copy the fifo to new container
		for (i = fifo->first; i != (fifo->last + 1) % fifo->mSize; i = (i + 1) % fifo->mSize) {
			temp[j] = fifo->elementArray[i];
			j++;
		}
		free (fifo->elementArray);
		fifo->elementArray = temp;
		fifo->first = 0;
		fifo->last = fifo->mSize - 1;
		fifo->mSize *= 2;
	}

	fifo->elementArray[fifo->last] = element;
	fifo->size++;
	fifo->last = (fifo->last + 1) % fifo->mSize;

}

void* FifoPop (Fifo* fifo) {

	if (fifo->size == 0) {
		ThrowException (CONTAINER_EMPTY_EXCEPTION);
	}

	fifo->size--;
	if (fifo->size == fifo->mSize / 4) {
		void** temp = (void**) malloc ( (fifo->mSize / 2) * sizeof (void*) );
		unsigned long i, j = 0;
		// Copy the fifo to new container
		for (i = fifo->first; i != (fifo->last + 1) % fifo->mSize; i = (i + 1) % fifo->mSize) {
			temp[j] = fifo->elementArray[i];
			j++;
		}
		free (fifo->elementArray);
		fifo->elementArray = temp;
		fifo->first = 0;
		fifo->last = j - 1;
		fifo->mSize /= 2;
	}

	void* temp = (void*)fifo->first;
	fifo->first = (fifo->first + 1) % fifo->mSize;
	return fifo->elementArray[(uintptr_t)temp];
}

Bool FifoIsEmpty (Fifo* fifo) {
	return (Bool) fifo->size == 0;
}

uintptr_t FifoSize (Fifo* fifo) {
	return fifo->size;
}
