#ifndef _STRING_T_H
#define _STRING_T_H

#include "bool.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _String {
	uintptr_t size;
	uintptr_t mSize; // Max size
	char* elementArray;
}String;

void StringInit (String* string);
void StringDelete (String* string);
void StringAppend (String* string, char element);
void StringInsert (String* string, char element, uintptr_t index);
char StringElement (String* string, uintptr_t index);
void StringConcatenate (String* to, String* from);
uintptr_t StringFind (String* string, char find);
Bool StringIsEmpty (String* string);
uintptr_t StringSize (String* string);
char* CString (String* string);
void StringSet (String* string, char cstr[]);
void StringPrint (FILE* stream, String* string);

#endif
