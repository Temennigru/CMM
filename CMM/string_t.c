#include "string_t.h"
#include "exception.h"
#include <stdlib.h>

void StringInit (String* string) {
	string->mSize = 100;
	string->size = 0;
	string->elementArray = (char*) malloc (100 * sizeof (char) );	
}

void StringDelete (String* string) {
	string->mSize = 0;
	string->size = 0;
	free (string->elementArray);
	string->elementArray = NULL; // To prevent another "delete then access" problem
}

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

void StringInsert (String* string, char element, uintptr_t index) {

	if (index > string->size - 1) {
		THROW (INDEX_OUT_OF_RANGE_EXCEPTION);
	}

	string->elementArray[index] = element;
}

char StringElement (String* string, uintptr_t index) {

	if (index > string->size - 1) {
		THROW (INDEX_OUT_OF_RANGE_EXCEPTION);
	}

	return string->elementArray[index];
}

void StringConcatenate (String* to, String* from) {
	unsigned int i;
	for (i = 0; i < StringSize (from); i++) {
		StringAppend (to, StringElement (from, i) );
	}
}

uintptr_t StringFind (String* string, char element) {
	unsigned int i;
	for (i = 0; i < string->size; i++) {
		if ( string->elementArray[i] == element) return i;
	}
	return -1;
}

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

Bool StringIsEmpty (String* string) {
	return (Bool) string->size == 0;
}

uintptr_t StringSize (String* string) {
	return string->size;
}

char* CString (String* string) {
	return string->elementArray;
}

void StringSet (String* string, char cstr[]) {
	int i;
	StringDelete (string);
	StringInit (string);
	for (i = 0; cstr[i] != '\0'; i++) {
		StringAppend(string, cstr[i]);
	}
}

void StringPrint (FILE* stream, String* string) {
	fprintf (stream, "%s", string->elementArray);
}
