#ifndef _LIST_H
#define _LIST_H

#include "bool.h"
#include <stdlib.h>

typedef struct _List {
	uintptr_t size;
	uintptr_t mSize; // Max size
	void** elementArray;
	Bool (* ListCompare) (void* a, void* b); // Implement this to change heap configuration
}List;

Bool StringListCompare (void* a, void* b); // Specialization of the default comparrison function
void ListInit (List* list, Bool (* ListCompare) (void*, void*) );
void ListDelete (List* list);
void ListAppend (List* list, void* element);
void ListInsert (List* list, void* element, uintptr_t index);
void* ListElement (List* list, uintptr_t index);
void ListConcatenate (List* to, List* from);
uintptr_t ListFind (List* list, void* find);
Bool ListIsEmpty (List* list);
uintptr_t ListSize (List* list);
uintptr_t ListEnd (List* list);
void ListClear (List* list);

#endif
