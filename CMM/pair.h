#ifndef _PAIR_H
#define _PAIR_H

typedef struct _Pair {
	void* first;
	void* second;
}Pair;

Pair* MakePair (void* first, void* second);


#endif
