#include "list.h"
#include "exception.h"
#include "string_t.h"
#include <string.h>
#include <stdlib.h>

// Not for use by external functions
Bool DefaultListCompare (void* a, void* b) { 
	return a == b;
}

/* Method: StringListComp
 * Parameters:
 * a - First String
 * b - Second String
 * Return value:
 * a == b
 * Description:
 * A specialization of list compare for strings. Compares the strings and returns.
 */

Bool StringListCompare (void* a, void* b) {
	return (Bool)!strcmp ( ( (String*)a)->elementArray, ( (String*)b)->elementArray);
}

/* Method: ListInit
 * Parameters:
 * list - Pointer to the List to be initialized
 * Return value:
 * none
 * Description:
 * Creates an array of 100 pointers, sets max size to 100 and resets element counter.
 */

void ListInit (List* list, Bool (* ListCompare) (void*, void*) ) {
	list->mSize = 100;
	list->size = 0;
	list->elementArray = (void**) malloc (100 * sizeof (void*) );	
	if (ListCompare != NULL) list->ListCompare = ListCompare;
	else list->ListCompare = DefaultListCompare;
}

/* Method: ListDelete
 * Parameters:
 * list - Pointer to the List to be deleted
 * Return value:
 * none
 * Description:
 * Deletes the container in list and sets max size to 0.
 */

void ListDelete (List* list) {
	list->mSize = 0;
	list->size = 0;
	free (list->elementArray);
	list->elementArray = NULL; // To prevent another "delete then access" problem
}

/* Method: ListAppend
 * Parameters:
 * list - Pointer to the List in which the element will be inserted
 * element  - Element to be inserted into the list
 * Return value:
 * none
 * Description:
 * Checks if size excedes max size to reallocate if necessary, then inserts
 * element to the top of the list.
 */

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

/* Method: ListInsert
 * Parameters:
 * list - Pointer to the List in which the element will be inserted
 * element - Element to insert into list
 * index - Index at which to insert element
 * Return value:
 * none
 * Description:
 * Insert an element on indexed list. If the index doesn't exist throw an exception.
 */

void ListInsert (List* list, void* element, uintptr_t index) {

	if (index > list->size - 1) {
		THROW (INDEX_OUT_OF_RANGE_EXCEPTION);
	}

	list->elementArray[index] = element;
}

/* Method: ListElement
 * Parameters:
 * list - Pointer to the List from which to retreive the element.
 * index - Index at which to retrieve the element.
 * Return value:
 * Returns the element stored in the specified index.
 * Description:
 * Checks if index is valid and retreives the respective element.
 */

void* ListElement (List* list, uintptr_t index) {

	if (index > list->size - 1) {
		THROW (INDEX_OUT_OF_RANGE_EXCEPTION);
	}

	return list->elementArray[index];
}

/* Method: ListConcatenate
 * Parameters:
 * to - List to which concatenate
 * from - List from which to concatenate
 * Return value:
 * none
 * Description:
 * Appends from to to.
 */

void ListConcatenate (List* to, List* from) {
	unsigned int i;
	for (i = 0; i < ListSize (from); i++) {
		ListAppend (to, ListElement (from, i) );
	}
}

/* Method: ListFind
 * Parameters:
 * list - List to search
 * element - Element to find
 * Return value:
 * Returns element if it was found and ListEnd if not.
 * Description:
 * Searchest list for element.
 */

uintptr_t ListFind (List* list, void* element) {
	uintptr_t i;
	for (i = 0; i < list->size; i++) {
		if ( list->ListCompare(list->elementArray[i], element) ) return i;
	}
	return ListEnd (list);
}


/* Method: ListRemove
 * Parameters:
 * list - Pointer to the List from which to remove the element.
 * index - Index at which to remove the element.
 * Return value:
 * none
 * Description:
 * Checks if index is valid and removes the respective element.
 * If list size gets lower than a specific threshold the max size is reduced.
 */

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

/* Method: ListIsEmpty
 * Parameters:
 * list - Pointer to the List to be checked
 * Return value:
 * Returns wether the list has any elements in it.
 * Description:
 * Returns wether size is 0 
 */

Bool ListIsEmpty (List* list) {
	return (Bool) list->size == 0;
}

/* Method: ListSize
 * Parameters:
 * list - Pointer to the List to be checked
 * Return value:
 * Returns the size of the list.
 * Description:
 * Returns list->size.
 */

uintptr_t ListSize (List* list) {
	return list->size;
}

/* Method: ListEnd
 * Parameters:
 * list - Pointer to the List to be checked
 * Return value:
 * Returns list->size.
 * Description:
 * Returns an iterator-like invalid element.
 */
uintptr_t ListEnd (List* list) {
	return list->size;
}

/* Method: ListClear
 * Parameters:
 * list - Pointer to the List to be cleared
 * Return value:
 * none
 * Description:
 * Resets the list.
 */
void ListClear (List* list) {
	list->elementArray = (void**) realloc (list->elementArray , 100 * sizeof (void*) );
	list->mSize = 100;
	list->size = 0;
}
