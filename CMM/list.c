#include "list.h"
#include "exception.h"
#include "string_t.h"
#include <string.h>
#include <stdlib.h>

// Not for use by external functions
Bool DefaultListCompare (void* a, void* b) { 
	return a == b;
}

Bool StringListCompare (void* a, void* b) {
	return (Bool)!strcmp ( ( (String*)a)->elementArray, ( (String*)b)->elementArray);
}

void ListInit (List* list, Bool (* ListCompare) (void*, void*) ) {
	list->mSize = 100;
	list->size = 0;
	list->elementArray = (void**) malloc (100 * sizeof (void*) );	
	if (ListCompare != NULL) list->ListCompare = ListCompare;
	else list->ListCompare = DefaultListCompare;
}

void ListDelete (List* list) {
	list->mSize = 0;
	list->size = 0;
	free (list->elementArray);
	list->elementArray = NULL; // To prevent another "delete then access" problem
}

void ListAppend (List* list, void* element) {
	if (list->size == list->mSize) {
		list->elementArray = (void**) realloc (list->elementArray, (100 + list->mSize) * sizeof (void*) );
		list->mSize += 100;
		if (list->elementArray == NULL) {
			list->mSize = 0;
			THROW (NOT_ENOUGH_MEMORY_EXCEPTION);
		}
	}

	list->elementArray[list->size] = element;
	list->size++;
}

void ListInsert (List* list, void* element, uintptr_t index) {

	if (index > list->size - 1) {
		THROW (INDEX_OUT_OF_RANGE_EXCEPTION);
	}

	list->elementArray[index] = element;
}

void* ListElement (List* list, uintptr_t index) {

	if (index > list->size - 1) {
		THROW (INDEX_OUT_OF_RANGE_EXCEPTION);
	}

	return list->elementArray[index];
}

void ListConcatenate (List* to, List* from) {
	unsigned int i;
	for (i = 0; i < ListSize (from); i++) {
		ListAppend (to, ListElement (from, i) );
	}
}

uintptr_t ListFind (List* list, void* element) {
	uintptr_t i;
	for (i = 0; i < list->size; i++) {
		if ( list->ListCompare(list->elementArray[i], element) ) return i;
	}
	return ListEnd (list);
}

void ListRemove (List* list, uintptr_t index) {

	unsigned long i;

	if (index > list->size - 1) {
		THROW (INDEX_OUT_OF_RANGE_EXCEPTION);
	}

	for(i = index; i < list->size - 1; i++) {
		list->elementArray[i] = list->elementArray[i + 1];
	}

	list->size--;

	if (list->size == list->mSize - 150) {
		list->elementArray = (void**) realloc (list->elementArray, (list->mSize - 100) * sizeof (void*) );
		list->mSize -= 100;
		if (list->elementArray == NULL) {
			list->mSize = 0;
			THROW (NOT_ENOUGH_MEMORY_EXCEPTION);
		}
	}
}

Bool ListIsEmpty (List* list) {
	return (Bool) list->size == 0;
}

uintptr_t ListSize (List* list) {
	return list->size;
}

uintptr_t ListEnd (List* list) {
	return list->size;
}

void ListClear (List* list) {
	list->elementArray = (void**) realloc (list->elementArray , 100 * sizeof (void*) );
	list->mSize = 100;
	list->size = 0;
}
