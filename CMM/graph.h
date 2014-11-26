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

/* Method: GraphInit
 * Parameters:
 * graph - Pointer to the Graph to be initialized.
 * nodeNumber - Number of nodes in the graph.
 * Return value:
 * none.
 * Description:
 * Allocates an incidence matrix and a list of node values.
 */

void GraphInit(Graph* graph, uintptr_t nodeNumber);

/* Method: GraphDelete
 * Parameters:
 * graph - Pointer to the Graph to be deleted.
 * Return value:
 * none
 * Description:
 * Deletes the containers in the graph and sets size to 0.
 */

void GraphDelete(Graph* graph);

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

void GraphSetEdge (Graph* graph, uintptr_t from, uintptr_t to, uintptr_t weight);

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
 
Bool GraphGetEdge (Graph* graph, uintptr_t from, uintptr_t to);

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

uintptr_t GraphGetEdgeWeight (Graph* graph, uintptr_t from, uintptr_t to);

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

void GraphSetNode (Graph* graph, uintptr_t node, void* value);

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

void GraphVisit (Graph* graph, uintptr_t node, void* visitor(void* node) );

/* Method: GraphSize
 * Parameters:
 * graph - Pointer to the graph to be checked.
 * Return value:
 * Returns the number of nodes in the graph
 * Description:
 * Returns graph->size.
 */

uintptr_t GraphSize (Graph* graph);

#endif
