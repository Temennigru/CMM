#include "heap.h"
#include "bool.h"
#include "exception.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Not for use of external functions

void swap (void** a, void** b) {
	void* temp = *a;
	*a = *b;
	*b = temp;
}

Bool DefaultHeapCompare (void* a, void* b) { 
	return a > b;
}

void HeapInit (Heap* heap, Bool (* HeapCompare) (void*, void*) ) {
	heap->mSize = 100;
	heap->size = 0;
	heap->elementArray = (void**) malloc (100 * sizeof (void*) );
	if (HeapCompare != NULL) heap->HeapCompare = HeapCompare;
	else heap->HeapCompare = DefaultHeapCompare;
}

void HeapDelete (Heap* heap) {
	heap->mSize = 0;
	heap->size = 0;
	free (heap->elementArray);
	heap->elementArray = NULL; // To prevent another "delete then access" problem
}

void HeapPush (Heap* heap, void* element) {
	if (heap->size == heap->mSize) {
		heap->elementArray = (void**) realloc (heap->elementArray, (100 + heap->mSize) * sizeof (void*) );
		heap->mSize += 100;
	}

	heap->elementArray[heap->size] = element;
	heap->size++;

	unsigned long i;
	for (i = heap->size - 1; i != 0; i = ceil((float)i/2.0) - 1 ) {
		if (heap->HeapCompare (heap->elementArray[(int)ceil((float)i/2.0) - 1], heap->elementArray[i]) ) {
			swap (&(heap->elementArray[i]),  &(heap->elementArray[(int)ceil((float)i/2.0) - 1]) );
		}
	}
}

void* HeapPop (Heap* heap) {

	if (heap->size == 0) {
		THROW (CONTAINER_EMPTY_EXCEPTION);
	}

	heap->size--;

	if (heap->size == heap->mSize - 150) {
		heap->elementArray = (void**) realloc (heap->elementArray, (heap->mSize - 100) * sizeof (void*) );
		heap->mSize -= 100;
                if (heap->elementArray == NULL) {
                        heap->mSize = 0;
                        THROW (NOT_ENOUGH_MEMORY_EXCEPTION);
                }
	}

	void* temp = heap->elementArray[0];

	if (heap->size == 0) {
		return temp;
	} else {
		heap->elementArray[0] = heap->elementArray[heap->size];
	}

	unsigned int i;
	// Reheapify
	for (i = 0;;) {
		// At most one child
		if ( ( (i + 1) * 2) > heap->size) {
			if ( (i * 2) + 1 == heap->size - 1 && heap->HeapCompare(heap->elementArray[i], heap->elementArray[( (i + 1) * 2) - 1]) ) {
				swap (&(heap->elementArray[i]), &(heap->elementArray[( (i + 1) * 2) - 1]) );
			}
			// No more children
			break;
		}
		// Left is smaller and right is not smalled than left
		else if (heap->HeapCompare (heap->elementArray[i], heap->elementArray[( (i + 1) * 2) - 1]) &&
			!heap->HeapCompare (heap->elementArray[(i * 2) + 1], heap->elementArray[(i + 1) * 2] ) ) {
			swap ( (&heap->elementArray[i]), &(heap->elementArray[(i * 2) + 1]) );
			i = (i * 2) + 1;
		// Right is smaller
		} else if (heap->HeapCompare (heap->elementArray[i], heap->elementArray[(i + 1) * 2]) ) {
			swap ( (&heap->elementArray[i]), &(heap->elementArray[(i + 1) * 2]) );
			i = (i + 1) * 2;
		} else break;
	}

	return temp;
}

Bool HeapIsEmpty (Heap* heap) {
	return (Bool) heap->size == 0;
}

uintptr_t HeapSize (Heap* heap) {
	return heap->size;
}

