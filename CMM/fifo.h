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

/* Method: FifoInit
 * Parameters:
 * fifo - Pointer to the Fifo to be initialized
 * Return value:
 * none
 * Description:
 * Creates an array of 100 pointers, sets max size to 100 and resets element counter.
 */

void FifoInit (Fifo* fifo);

/* Method: FifoDelete
 * Parameters:
 * fifo - Pointer to the Fifo to be deleted
 * Return value:
 * none
 * Description:
 * Deletes the container in fifo and sets max size to 0.
 */

void FifoDelete (Fifo* fifo);

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

void FifoPush (Fifo* fifo, void* element);

/* Method: FifoPop
 * Parameters:
 * fifo - Pointer to the Fifo in which the element will be inserted
 * Return value:
 * Returns the popped node.
 * Description:
 * Pops the top of the fifo and returns it. If the fifo size passes
 * a maximum threshold of 50, the size is reduced.
 */

void* FifoPop (Fifo* fifo);

/* Method: FifoIsEmpty
 * Parameters:
 * fifo - Pointer to the Fifo to be checked
 * Return value:
 * Returns wether the fifo has any elements in it.
 * Description:
 * Returns wether fifo size is 0.
 */

Bool FifoIsEmpty (Fifo* fifo);

/* Method: FifoSize
 * Parameters:
 * fifo - Pointer to the Fifo to be checked
 * Return value:
 * Returns the size of the fifo.
 * Description:
 * Returns fifo->size.
 */
 
uintptr_t FifoSize (Fifo* fifo);

#endif
