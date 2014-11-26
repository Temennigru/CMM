#include "stack.h"
#include "bool.h"
#include "exception.h"
#include <stdlib.h>

void StackInit (Stack* stack) {
	stack->mSize = 100;
	stack->size = 0;
	stack->elementArray = (void**) malloc (100 * sizeof (void*) );	
}

void StackDelete (Stack* stack) {
	stack->mSize = 0;
	stack->size = 0;
	free (stack->elementArray);
	stack->elementArray = NULL; // To prevent another "delete then access" problem
}

void StackPush (Stack* stack, void* element) {
	if (stack->size == stack->mSize) {
		stack->elementArray = (void**) realloc (stack->elementArray, (100 + stack->mSize) * sizeof (void*) );
		stack->mSize += 100;
	}

	stack->elementArray[stack->size] = element;
	stack->size++;
}

void* StackPop (Stack* stack) {

	if (stack->size == 0) {
		ThrowException (CONTAINER_EMPTY_EXCEPTION);
	}

	stack->size--;

	if (stack->size == stack->mSize - 150) {
		stack->elementArray = (void**) realloc (stack->elementArray, (stack->mSize - 100) * sizeof (void*) );
		stack->mSize -= 100;
                if (stack->elementArray == NULL) {
                        stack->mSize = 0;
                        ThrowException (NOT_ENOUGH_MEMORY_EXCEPTION);
                }
	}

	return stack->elementArray[stack->size];
}

Bool StackIsEmpty (Stack* stack) {
	return (Bool) stack->size == 0;
}

uintptr_t StackSize (Stack* stack) {
	return stack->size;
}
