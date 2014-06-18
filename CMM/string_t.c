#include "string_t.h"
#include "exception.h"
#include <stdlib.h>

/* Method: StringInit
 * Parameters:
 * String - Pointer to the String to be initialized
 * Return value:
 * none
 * Description:
 * Creates an array of 100 pointers, sets max size to 100 and resets element counter.
 */

void StringInit (String* string) {
	string->mSize = 100;
	string->size = 0;
	string->elementArray = (char*) malloc (100 * sizeof (char) );	
}

/* Method: StringDelete
 * Parameters:
 * String - Pointer to the String to be deleted
 * Return value:
 * none
 * Description:
 * Deletes the container in String and sets max size to 0.
 */

void StringDelete (String* string) {
	string->mSize = 0;
	string->size = 0;
	free (string->elementArray);
	string->elementArray = NULL; // To prevent another "delete then access" problem
}

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

void StringAppend (String* string, char element) {
	if (string->size + 1 >= string->mSize) {
		string->elementArray = (char*) realloc (string->elementArray, (2 * string->mSize) * sizeof (char) );
		string->mSize *= 2;
		if (string->elementArray == NULL) {
			string->mSize = 0;
			THROW (NOT_ENOUGH_MEMORY_EXCEPTION);
		}
	}

	string->elementArray[string->size] = element;
	string->elementArray[string->size + 1] = '\0';
	string->size++;
}

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

void StringInsert (String* string, char element, uintptr_t index) {

	if (index > string->size - 1) {
		THROW (INDEX_OUT_OF_RANGE_EXCEPTION);
	}

	string->elementArray[index] = element;
}

/* Method: StringElement
 * Parameters:
 * String - Pointer to the String from which to retreive the element.
 * index - Index at which to retrieve the element.
 * Return value:
 * Returns the element stored in the specified index.
 * Description:
 * Checks if index is valid and retreives the respective element.
 */

char StringElement (String* string, uintptr_t index) {

	if (index > string->size - 1) {
		THROW (INDEX_OUT_OF_RANGE_EXCEPTION);
	}

	return string->elementArray[index];
}

/* Method: StringConcatenate
 * Parameters:
 * to - String to which concatenate
 * from - String from which to concatenate
 * Return value:
 * none
 * Description:
 * Appends from to to.
 */

void StringConcatenate (String* to, String* from) {
	unsigned int i;
	for (i = 0; i < StringSize (from); i++) {
		StringAppend (to, StringElement (from, i) );
	}
}

/* Method: StringFind
 * Parameters:
 * String - String to search
 * element - Element to find
 * Return value:
 * Returns whether element was found
 * Description:
 * Searchest String for element.
 */

uintptr_t StringFind (String* string, char element) {
	unsigned int i;
	for (i = 0; i < string->size; i++) {
		if ( string->elementArray[i] == element) return i;
	}
	return -1;
}
	

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

void StringRemove (String* string, uintptr_t index) {

	unsigned long i;

	if (index > string->size - 1) {
		THROW (INDEX_OUT_OF_RANGE_EXCEPTION);
	}

	for(i = index; i < string->size - 1; i++) {
		string->elementArray[i] = string->elementArray[i + 1];
	}

	string->size--;

	if (string->size == string->mSize / 4 && string->size > 100) {
		string->elementArray = (char*) realloc (string->elementArray, (string->mSize / 2) * sizeof (char) );
		string->mSize /= 2;
		if (string->elementArray == NULL) {
			string->mSize = 0;
			THROW (NOT_ENOUGH_MEMORY_EXCEPTION);
		}
	}
}

/* Method: StringIsEmpty
 * Parameters:
 * String - Pointer to the String to be checked
 * Return value:
 * Returns wether the String has any elements in it.
 * Description:
 * Returns wether size is 0 
 */

Bool StringIsEmpty (String* string) {
	return (Bool) string->size == 0;
}

/* Method: StringSize
 * Parameters:
 * String - Pointer to the String to be checked
 * Return value:
 * Returns the size of the String.
 * Description:
 * Returns String->size.
 */

uintptr_t StringSize (String* string) {
	return string->size;
}

/* Method: CString
 * Parameters:
 * String - Pointer to the String
 * Return value:
 * Returns the equivalent character array.
 * Description:
 * Returns String->elementArray.
 */
char* CString (String* string) {
	return string->elementArray;
}

/* Method: StringSet
 * Parameters:
 * string - Pointer to the String
 * cstr - c_str to set to string
 * Return value:
 * none
 * Description:
 * Sets string to the c_string value.
 */
void StringSet (String* string, char cstr[]) {
	int i;
	StringDelete (string);
	StringInit (string);
	for (i = 0; cstr[i] != '\0'; i++) {
		StringAppend(string, cstr[i]);
	}
}

/* Method: StringPrint
 * Parameters:
 * stream - stream to which the method will print the string
 * string - Pointer to the String
 * Return value:
 * none
 * Description:
 * Prints the string to the stream.
 */
void StringPrint (FILE* stream, String* string) {
	fprintf (stream, "%s", string->elementArray);
}
