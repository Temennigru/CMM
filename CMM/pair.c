#include "pair.h"
#include <stdlib.h>

Pair* MakePair (void* first, void* second) {
	Pair* ret = (Pair*) malloc (sizeof (Pair) );

	ret->first = first;
	ret->second = second;

	return ret;
}
