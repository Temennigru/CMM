#include "stack.h"
#include "bool.h"
#include "exception.h"
#include <stdlib.h>

/* Method: StackInit
 * Parameters:
 * stack - Pointer to the Stack to be initialized
 * Return value:
 * none
 * Description:
 * Creates an array of 100 pointers, sets max size to 100 and resets element counter.
 */

void StackInit (Stack* stack) {
	stack->mSize = 100;
	stack->size = 0;
	stack->elementArray = (void**) malloc (100 * sizeof (void*) );	
}

/* Method: StackDelete
 * Parameters:
 * stack - Pointer to the Stack to be deleted
 * Return value:
 * none
 * Description:
 * Deletes the container in stack and sets max size to 0.
 */

void StackDelete (Stack* stack) {
	stack->mSize = 0;
	stack->size = 0;
	free (stack->elementArray);
	stack->elementArray = NULL; // To prevent another "delete then access" problem
}

/* Method: StackPush
 * Parameters:
 * stack - Pointer to the Stack in which the element will be inserted
 * element  - Element to be inserted into the stack
 * Return value:
 * none
 * Description:
 * Checks if size excedes max size to reallocate if necessary, then inserts
 * element to the top of the stack.
 */

void StackPush (Stack* stack, void* element) {
	if (stack->size == stack->mSize) {
		stack->elementArray = (void**) realloc (stack->elementArray, (100 + stack->mSize) * sizeof (void*) );
		stack->mSize += 100;
	}

	stack->elementArray[stack->size] = element;
	stack->size++;
}

/* Method: StackPop
 * Parameters:
 * stack - Pointer to the Stack in which the element will be inserted
 * Return value:
 * Returns the popped node.
 * Description:
 * Pops the top of the stack and returns it. If the stack size passes
 * a maximum threshold of 50, the size is reduced.
 */

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

/* Method: StackIsEmpty
 * Parameters:
 * stack - Pointer to the Stack to be checked
 * Return value:
 * Returns wether the stack has any elements in it.
 * Description:
 * Returns wether stack size is 0.
 */

Bool StackIsEmpty (Stack* stack) {
	return (Bool) stack->size == 0;
}

/* Method: StackSize
 * Parameters:
 * stack - Pointer to the Stack to be checked
 * Return value:
 * Returns the size of the stack.
 * Description:
 * Returns stack->size.
 */

uintptr_t StackSize (Stack* stack) {
	return stack->size;
}
