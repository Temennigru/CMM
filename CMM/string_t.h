#ifndef _STRING_T_H
#define _STRING_T_H

#include "bool.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _String {
	uintptr_t size;
	uintptr_t mSize; // Max size
	char* elementArray;
} String;


/* Method: StringInit
 * Parameters:
 * String - Pointer to the String to be initialized
 * Return value:
 * none
 * Description:
 * Creates an array of 100 pointers, sets max size to 100 and resets element counter.
 */

void StringInit (String* string);

/* Method: StringDelete
 * Parameters:
 * String - Pointer to the String to be deleted
 * Return value:
 * none
 * Description:
 * Deletes the container in String and sets max size to 0.
 */

void StringDelete (String* string);

/* Method: StringAppend
 * Parameters:
 * String - Pointer to the String in which the element will be inserted
 * element  - Element to be inserted into the String
 * Return value:
 * none
 * Description:
 * Checks if size excedes max size to reallocate if necessary, then inserts
 * element to the top of the String.
 */

void StringAppend (String* string, char element);

/* Method: StringInsert
 * Parameters:
 * String - Pointer to the String in which the element will be inserted
 * element - Element to insert into String
 * index - Index at which to insert element
 * Return value:
 * none
 * Description:
 * Insert an element on indexed String. If the index doesn't exist throw an exception.
 */

void StringInsert (String* string, char element, uintptr_t index);

/* Method: StringElement
 * Parameters:
 * String - Pointer to the String from which to retreive the element.
 * index - Index at which to retrieve the element.
 * Return value:
 * Returns the element stored in the specified index.
 * Description:
 * Checks if index is valid and retreives the respective element.
 */

char StringElement (String* string, uintptr_t index);

/* Method: StringConcatenate
 * Parameters:
 * to - String to which concatenate
 * from - String from which to concatenate
 * Return value:
 * none
 * Description:
 * Appends from to to.
 */

void StringConcatenate (String* to, String* from);

/* Method: StringFind
 * Parameters:
 * String - String to search
 * element - Element to find
 * Return value:
 * Returns whether element was found
 * Description:
 * Searchest String for element.
 */

uintptr_t StringFind (String* string, char find);

/* Method: StringRemove
 * Parameters:
 * String - Pointer to the String from which to remove the element.
 * index - Index at which to remove the element.
 * Return value:
 * none
 * Description:
 * Checks if index is valid and removes the respective element.
 * If String size gets lower than a specific threshold the max size is reduced.
 */

void StringRemove (String* string, uintptr_t index);

/* Method: StringIsEmpty
 * Parameters:
 * String - Pointer to the String to be checked
 * Return value:
 * Returns wether the String has any elements in it.
 * Description:
 * Returns wether size is 0 
 */

Bool StringIsEmpty (String* string);

/* Method: StringSize
 * Parameters:
 * String - Pointer to the String to be checked
 * Return value:
 * Returns the size of the String.
 * Description:
 * Returns String->size.
 */

uintptr_t StringSize (String* string);

/* Method: CString
 * Parameters:
 * String - Pointer to the String
 * Return value:
 * Returns the equivalent character array.
 * Description:
 * Returns String->elementArray.
 */

char* CString (String* string);

/* Method: StringSet
 * Parameters:
 * string - Pointer to the String
 * cstr - c_str to set to string
 * Return value:
 * none
 * Description:
 * Sets string to the c_string value.
 */

void StringSet (String* string, char cstr[]);

/* Method: StringPrint
 * Parameters:
 * stream - stream to which the method will print the string
 * string - Pointer to the String
 * Return value:
 * none
 * Description:
 * Prints the string to the stream.
 */

void StringPrint (FILE* stream, String* string);

#endif
