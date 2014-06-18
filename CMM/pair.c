#include "pair.h"
#include <stdlib.h>

/* Method: MakePair
 * Parameters:
 * first - First element of the pair
 * second - Second element of the pair
 * Return value:
 * Returns pointer to created pair.
 * Description:
 * Allocates a pair, adds first and second to it and returns the pointer.
 */

Pair* MakePair (void* first, void* second) {
	Pair* ret = (Pair*) malloc (sizeof (Pair) );

	ret->first = first;
	ret->second = second;

	return ret;
}
