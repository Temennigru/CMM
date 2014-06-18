#include "fifo.h"
#include "bool.h"
#include "exception.h"
#include <stdlib.h>

/* Method: FifoInit
 * Parameters:
 * fifo - Pointer to the Fifo to be initialized
 * Return value:
 * none
 * Description:
 * Creates an array of 100 pointers, sets max size to 100 and resets element counter.
 */

void FifoInit (Fifo* fifo) {
	fifo->mSize = 100;
	fifo->size = 0;
	fifo->first = 0;
	fifo->last = 0;
	fifo->elementArray = (void**) malloc (100 * sizeof (void*) );	
}

/* Method: FifoDelete
 * Parameters:
 * fifo - Pointer to the Fifo to be deleted
 * Return value:
 * none
 * Description:
 * Deletes the container in fifo and sets max size to 0.
 */

void FifoDelete (Fifo* fifo) {
	fifo->mSize = 0;
	fifo->size = 0;
	fifo->first = 0;
	fifo->last = 0;
	free (fifo->elementArray);
	fifo->elementArray = NULL; // To prevent another "delete then access" problem
}

/* Method: FifoPush
 * Parameters:
 * fifo - Pointer to the Fifo in which the element will be inserted
 * element  - Element to be inserted into the fifo
 * Return value:
 * none
 * Description:
 * Checks if size excedes max size to reallocate if necessary, then inserts
 * element to the end of the fifo.
 */

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

/* Method: FifoPop
 * Parameters:
 * fifo - Pointer to the Fifo in which the element will be inserted
 * Return value:
 * Returns the popped node.
 * Description:
 * Pops the top of the fifo and returns it. If the fifo size passes
 * a maximum threshold of 50, the size is reduced.
 */

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

/* Method: FifoIsEmpty
 * Parameters:
 * fifo - Pointer to the Fifo to be checked
 * Return value:
 * Returns wether the fifo has any elements in it.
 * Description:
 * Returns wether fifo size is 0.
 */

Bool FifoIsEmpty (Fifo* fifo) {
	return (Bool) fifo->size == 0;
}

/* Method: FifoSize
 * Parameters:
 * fifo - Pointer to the Fifo to be checked
 * Return value:
 * Returns the size of the fifo.
 * Description:
 * Returns fifo->size.
 */

uintptr_t FifoSize (Fifo* fifo) {
	return fifo->size;
}
