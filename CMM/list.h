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

/* Method: StringListCompare
 * Parameters:
 * a - First String
 * b - Second String
 * Return value:
 * a == b
 * Description:
 * A specialization of list compare for strings. Compares the strings and returns.
 */

Bool StringListCompare (void* a, void* b); // Specialization of the default comparrison function

/* Method: ListInit
 * Parameters:
 * list - Pointer to the List to be initialized
 * Return value:
 * none
 * Description:
 * Creates an array of 100 pointers, sets max size to 100 and resets element counter.
 */

void ListInit (List* list, Bool (* ListCompare) (void*, void*) );

/* Method: ListDelete
 * Parameters:
 * list - Pointer to the List to be deleted
 * Return value:
 * none
 * Description:
 * Deletes the container in list and sets max size to 0.
 */

void ListDelete (List* list);

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

void ListAppend (List* list, void* element);

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

void ListInsert (List* list, void* element, uintptr_t index);

/* Method: ListElement
 * Parameters:
 * list - Pointer to the List from which to retreive the element.
 * index - Index at which to retrieve the element.
 * Return value:
 * Returns the element stored in the specified index.
 * Description:
 * Checks if index is valid and retreives the respective element.
 */

void* ListElement (List* list, uintptr_t index);

/* Method: ListConcatenate
 * Parameters:
 * to - List to which concatenate
 * from - List from which to concatenate
 * Return value:
 * none
 * Description:
 * Appends from to to.
 */

void ListConcatenate (List* to, List* from);

/* Method: ListFind
 * Parameters:
 * list - List to search
 * element - Element to find
 * Return value:
 * Returns element if it was found and ListEnd if not.
 * Description:
 * Searchest list for element.
 */

uintptr_t ListFind (List* list, void* find);


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

 void ListRemove (List* list, uintptr_t index);

/* Method: ListIsEmpty
 * Parameters:
 * list - Pointer to the List to be checked
 * Return value:
 * Returns wether the list has any elements in it.
 * Description:
 * Returns wether size is 0 
 */

Bool ListIsEmpty (List* list);

/* Method: ListSize
 * Parameters:
 * list - Pointer to the List to be checked
 * Return value:
 * Returns the size of the list.
 * Description:
 * Returns list->size.
 */

uintptr_t ListSize (List* list);

/* Method: ListEnd
 * Parameters:
 * list - Pointer to the List to be checked
 * Return value:
 * Returns list->size.
 * Description:
 * Returns an iterator-like invalid element.
 */

uintptr_t ListEnd (List* list);

/* Method: ListClear
 * Parameters:
 * list - Pointer to the List to be cleared
 * Return value:
 * none
 * Description:
 * Resets the list.
 */
 
void ListClear (List* list);

#endif
