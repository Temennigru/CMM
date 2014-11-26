#ifndef _PAIR_H
#define _PAIR_H

typedef struct _Pair {
	void* first;
	void* second;
}Pair;

/* Method: MakePair
 * Parameters:
 * first - First element of the pair
 * second - Second element of the pair
 * Return value:
 * Returns pointer to created pair.
 * Description:
 * Allocates a pair, adds first and second to it and returns the pointer.
 */

Pair* MakePair (void* first, void* second);


#endif
