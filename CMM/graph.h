#ifndef _GRAPH_H
#define _GRAPH_H

#include "bool.h"
#include "matrix.h"
#include "list.h"

typedef struct _Graph {
	Matrix incidenceMatrix;
	Matrix edgeValues;

	List nodeList;

	uintptr_t size;
} Graph;

void GraphInit(Graph* graph, uintptr_t nodeNumber);
void GraphDelete(Graph* graph);
void GraphSetEdge (Graph* graph, uintptr_t from, uintptr_t to, uintptr_t weight);
Bool GraphGetEdge (Graph* graph, uintptr_t from, uintptr_t to);
uintptr_t GraphGetEdgeWeight (Graph* graph, uintptr_t from, uintptr_t to);
void GraphSetNode (Graph* graph, uintptr_t node, void* value);
void GraphVisit (Graph* graph, uintptr_t node, void* visitor(void* node) );
uintptr_t GraphSize (Graph* graph);

#endif
