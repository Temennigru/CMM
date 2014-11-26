#ifndef _HEAP_H
#define _HEAP_H

#include "bool.h"
#include <stdlib.h>

typedef struct _Heap {
	uintptr_t size;
	uintptr_t mSize; // Max size
	void** elementArray;
	Bool (* HeapCompare) (void* a, void* b); // Implement this to change heap configuration
} Heap;

/* Method: HeapInit
 * Parameters:
 * heap - Pointer to the Heap to be initialized
 * Return value:
 * none
 * Description:
 * Creates an array of 100 pointers, sets max size to 100 and resets element counter.
 */

void HeapInit (Heap* heap, Bool (*HeapCompare) (void* el1, void* el2) );

/* Method: HeapDelete
 * Parameters:
 * heap - Pointer to the Heap to be deleted
 * Return value:
 * none
 * Description:
 * Deletes the container in heap and sets max size to 0.
 */

void HeapDelete (Heap* heap);

/* Method: HeapPush
 * Parameters:
 * heap - Pointer to the Heap in which the element will be inserted
 * element  - Element to be inserted into the heap
 * Return value:
 * none
 * Description:
 * Checks if size excedes max size to reallocate if necessary, then inserts
 * element to the top of the heap.
 */

void HeapPush (Heap* heap, void* element);

/* Method: HeapPop
 * Parameters:
 * heap - Pointer to the Heap in which the element will be inserted
 * Return value:
 * Returns the popped node.
 * Description:
 * Pops the top of the heap and returns it. If the heap size passes
 * a maximum threshold of 50, the size is reduced.
 */

void* HeapPop (Heap* heap);

/* Method: HeapIsEmpty
 * Parameters:
 * heap - Pointer to the Heap to be checked
 * Return value:
 * Returns wether the heap has any elements in it.
 * Description:
 * Returns wether heap size is 0.
 */

Bool HeapIsEmpty (Heap* heap);

/* Method: HeapSize
 * Parameters:
 * heap - Pointer to the Heap to be checked
 * Return value:
 * Returns the size of the heap.
 * Description:
 * Returns heap->size.
 */
 
uintptr_t HeapSize (Heap* heap);

#endif
