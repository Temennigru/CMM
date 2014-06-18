#ifndef _STACK_H
#define _STACK_H

#include "bool.h"
#include <stdlib.h>

typedef struct _Stack {
	uintptr_t size;
	uintptr_t mSize; // Max size
	void** elementArray;
}Stack;

void StackInit (Stack* stack);
void StackDelete (Stack* stack);
void StackPush (Stack* stack, void* element);
void* StackPop (Stack* stack);
Bool StackIsEmpty (Stack* stack);
uintptr_t StackSize (Stack* stack);

#endif
