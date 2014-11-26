#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct _Matrix {
	long sizeX, sizeY;
	void*** elementMatrix;
} Matrix;

/* Method: MatrixInit
 * Parameters:
 * mat - Pointer to the Matrix to be initialized
 * Return value:
 * none
 * Description:
 * Creates a Matrix of a specified size.
 */

void MatrixInit (Matrix* mat, long sizeX, long sizeY);

/* Method: MatrixDelete
 * Parameters:
 * matrix - Pointer to the Matrix to be deleted
 * Return value:
 * none
 * Description:
 * Deletes the container matrix.
 */

void MatrixDelete (Matrix* mat);

/* Method: MatrixSetElement
 * Parameters:
 * mat - Pointer to the matrix in which to modify the element.
 * element  - Element to be inserted into the matrix
 * indexX - X coordinates in which to insert the element.
 * indexY - Y coordinates in which to insert the element.
 * Return value:
 * none
 * Description:
 * Checks if coordinates are out of range and sets the specified element.
 */

void MatrixSetElement (Matrix* mat, void* element, long indexX, long indexY);

/* Method: MatrixExpand
 * Parameters:
 * mat - Pointer to the matrix to be expanded.
 * newSizeX - Size X to which expand. Pass 0 to leave unaltered.
 * newSizeY - Size Y to which expand. Pass 0 to leave unaltered.
 * Return value:
 * none
 * Description:
 * Checks if new sizes are expanding the matrix and reallocates the size of the matrix.
 */

void MatrixExpand (Matrix* mat, long newSizeX, long newSizeY);

/* Method: MatrixElement
 * Parameters:
 * mat - Pointer to the Matrix from which to retreive the element.
 * indexX - Index X at which to retrieve the element.
 * indexy - Index Y at which to retrieve the element.
 * Return value:
 * Returns the element stored in the specified coordinates.
 * Description:
 * Checks if coordinates are valid and retreives the respective element.
 */

void* MatrixElement (Matrix* mat, long indexX, long indexY);

/* Method: MatrixSize
 * Parameters:
 * mat - Pointer to the Matrix to be checked.
 * whichSize - Which size to get (x or y)
 * Return value:
 * Returns wether the specified size of the Matrix.
 * Description:
 * Returns mat->size(X | Y).
 */
 
long MatrixSize (Matrix* mat, char whichSize);

#endif
