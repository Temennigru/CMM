#ifndef _STACK_H
#define _STACK_H

#include "bool.h"
#include <stdlib.h>

typedef struct _Stack {
	uintptr_t size;
	uintptr_t mSize; // Max size
	void** elementArray;
}Stack;


/* Method: StackInit
 * Parameters:
 * stack - Pointer to the Stack to be initialized
 * Return value:
 * none
 * Description:
 * Creates an array of 100 pointers, sets max size to 100 and resets element counter.
 */

void StackInit (Stack* stack);

/* Method: StackDelete
 * Parameters:
 * stack - Pointer to the Stack to be deleted
 * Return value:
 * none
 * Description:
 * Deletes the container in stack and sets max size to 0.
 */

void StackDelete (Stack* stack);

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

void StackPush (Stack* stack, void* element);

/* Method: StackPop
 * Parameters:
 * stack - Pointer to the Stack in which the element will be inserted
 * Return value:
 * Returns the popped node.
 * Description:
 * Pops the top of the stack and returns it. If the stack size passes
 * a maximum threshold of 50, the size is reduced.
 */

void* StackPop (Stack* stack);

/* Method: StackIsEmpty
 * Parameters:
 * stack - Pointer to the Stack to be checked
 * Return value:
 * Returns wether the stack has any elements in it.
 * Description:
 * Returns wether stack size is 0.
 */

Bool StackIsEmpty (Stack* stack);

/* Method: StackSize
 * Parameters:
 * stack - Pointer to the Stack to be checked
 * Return value:
 * Returns the size of the stack.
 * Description:
 * Returns stack->size.
 */
 
uintptr_t StackSize (Stack* stack);

#endif
