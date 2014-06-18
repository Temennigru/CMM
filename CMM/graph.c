#include <stdlib.h>
#include "matrix.h"
#include "graph.h"
#include "exception.h"

/* Method: GraphInit
 * Parameters:
 * graph - Pointer to the Graph to be initialized.
 * nodeNumber - Number of nodes in the graph.
 * Return value:
 * none.
 * Description:
 * Allocates an incidence matrix and a list of node values.
 */

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

/* Method: GraphDelete
 * Parameters:
 * graph - Pointer to the Graph to be deleted.
 * Return value:
 * none
 * Description:
 * Deletes the containers in the graph and sets size to 0.
 */

void GraphDelete(Graph* graph) {
	MatrixDelete (&(graph->incidenceMatrix) );
	MatrixDelete (&(graph->edgeValues) );
	ListDelete (&(graph->nodeList) );
	graph->size = 0;
}

/* Method: GraphSetEdge
 * Parameters:
 * graph - Pointer to the graph to be modified.
 * from - ID of the first node in the edge.
 * to - ID of the second node in the edge.
 * Return value:
 * none
 * Description:
 * Sets the value of both cells in the incidence matrix to TRUE.
 */

void GraphSetEdge (Graph* graph, uintptr_t from, uintptr_t to, uintptr_t weight) {
	MatrixSetElement (&(graph->incidenceMatrix), (void*) TRUE, from, to);
	MatrixSetElement (&(graph->edgeValues), (void*) weight, from, to);
}

/* Method: GraphGetEdge
 * Parameters:
 * graph - Pointer to the graph to be consulted.
 * from - ID of the first node in the edge.
 * to - ID of the second node in the edge.
 * Return value:
 * Returns wether the edge exists.
 * Description:
 * Returns the value of the specified cell.
 */

Bool GraphGetEdge (Graph* graph, uintptr_t from, uintptr_t to) {
	return (Bool) MatrixElement (&(graph->incidenceMatrix), from, to);
}

/* Method: GraphGetEdgeWeight
 * Parameters:
 * graph - Pointer to the graph to be consulted.
 * from - ID of the first node in the edge.
 * to - ID of the second node in the edge.
 * Return value:
 * Returns wether the edge exists.
 * Description:
 * Returns the value of the specified cell.
 */

uintptr_t GraphGetEdgeWeight (Graph* graph, uintptr_t from, uintptr_t to) {
	return (Bool) MatrixElement (&(graph->edgeValues), from, to);
}

/* Method: GraphSetNode
 * Parameters:
 * graph - Pointer to the graph to be modified.
 * node - ID of the node to be set.
 * value - value to be stored in the node.
 * Return value:
 * none
 * Description:
 * Inserts the value into the node list.
 */

void GraphSetNode (Graph* graph, uintptr_t node, void* value) {
	ListInsert (&(graph->nodeList), value, node);
}

/* Method: GraphVisit
 * Parameters:
 * graph - Pointer to the graph to be visited.
 * node - ID of the node to be visited.
 * visitor - Pointer to a function to be called. Function must have the signature "void *visitorName* (void* node)".
 * Return value:
 * none
 * Description:
 * Calls the specified function with the specified node as a parameter.
 */

void GraphVisit (Graph* graph, uintptr_t node, void* visitor (void* node) ) {
	visitor (ListElement (&(graph->nodeList), node) );
}

/* Method: GraphSize
 * Parameters:
 * graph - Pointer to the graph to be checked.
 * Return value:
 * Returns the number of nodes in the graph
 * Description:
 * Returns graph->size.
 */

uintptr_t GraphSize (Graph* graph) {
	return graph->size;
}
