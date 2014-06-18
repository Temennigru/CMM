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

void HeapInit (Heap* heap, Bool (*HeapCompare) (void* el1, void* el2) );
void HeapDelete (Heap* heap);
void HeapPush (Heap* heap, void* element);
void* HeapPop (Heap* heap);
Bool HeapIsEmpty (Heap* heap);
uintptr_t HeapSize (Heap* heap);

#endif
