#include <stdlib.h>
#include "matrix.h"
#include "graph.h"
#include "exception.h"

void GraphInit(Graph* graph, uintptr_t nodeNumber) {

	MatrixInit (&(graph->incidenceMatrix), nodeNumber, nodeNumber);
	MatrixInit (&(graph->edgeValues), nodeNumber, nodeNumber);
	ListInit (&(graph->nodeList), NULL );
	uintptr_t i;
	for (i = 0; i < nodeNumber; i++) {
		ListAppend (&(graph->nodeList), NULL);
	}
	graph->size = nodeNumber;
}

void GraphDelete(Graph* graph) {
	MatrixDelete (&(graph->incidenceMatrix) );
	MatrixDelete (&(graph->edgeValues) );
	ListDelete (&(graph->nodeList) );
	graph->size = 0;
}

void GraphSetEdge (Graph* graph, uintptr_t from, uintptr_t to, uintptr_t weight) {
	MatrixSetElement (&(graph->incidenceMatrix), (void*) TRUE, from, to);
	MatrixSetElement (&(graph->edgeValues), (void*) weight, from, to);
}

Bool GraphGetEdge (Graph* graph, uintptr_t from, uintptr_t to) {
	return (Bool) MatrixElement (&(graph->incidenceMatrix), from, to);
}

uintptr_t GraphGetEdgeWeight (Graph* graph, uintptr_t from, uintptr_t to) {
	return (Bool) MatrixElement (&(graph->edgeValues), from, to);
}

void GraphSetNode (Graph* graph, uintptr_t node, void* value) {
	ListInsert (&(graph->nodeList), value, node);
}

void GraphVisit (Graph* graph, uintptr_t node, void* visitor (void* node) ) {
	visitor (ListElement (&(graph->nodeList), node) );
}

uintptr_t GraphSize (Graph* graph) {
	return graph->size;
}
