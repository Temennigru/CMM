#include <stdlib.h>
#include "list.h"
#include "exception.h"
#include "matrix.h"

/* Method: MatrixInit
 * Parameters:
 * mat - Pointer to the Matrix to be initialized
 * Return value:
 * none
 * Description:
 * Creates a Matrix of a specified size.
 */

void MatrixInit (Matrix* mat, long sizeX, long sizeY) {
	int i, j;

	mat->sizeX = sizeX;
	mat->sizeY = sizeY;
	mat->elementMatrix = (void***) malloc (sizeX * sizeof (void**) );	

	for (i = 0; i < mat->sizeX; i++) {
		mat->elementMatrix[i] = (void**) malloc (sizeY * sizeof (void*) );	
		for (j = 0; j < mat->sizeY; j++) {
			mat->elementMatrix[i][j] = NULL;
		}
	}
}

/* Method: MatrixDelete
 * Parameters:
 * matrix - Pointer to the Matrix to be deleted
 * Return value:
 * none
 * Description:
 * Deletes the container matrix.
 */

void MatrixDelete (Matrix* mat) {
	int i;
	for (i = 0; i < mat->sizeX; i++) {
		free (mat->elementMatrix[i]);
	}
	free (mat->elementMatrix);
	mat->sizeX = 0;
	mat->sizeY = 0;
	mat->elementMatrix = NULL; // To prevent another "delete then access" problem
}

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

void MatrixSetElement (Matrix* mat, void* element, long indexX, long indexY) {
	if (indexX > mat->sizeX - 1 || indexY > mat->sizeY - 1) {
		ThrowException (INDEX_OUT_OF_RANGE_EXCEPTION);
	} else if (indexX < 0 || indexY < 0) {
		ThrowException (NEGATIVE_INDEX_OR_SIZE);
	}

	mat->elementMatrix[indexX][indexY] = element;
}	

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

void MatrixExpand (Matrix* mat, long newSizeX, long newSizeY) {

	if (newSizeX == 0) {
		newSizeX = mat->sizeX;
        } else if (newSizeX < 0) {
		ThrowException (NEGATIVE_INDEX_OR_SIZE);
	} else if (newSizeX < mat->sizeX) {
		ThrowException (MATRIX_RESIZE_NOT_GREATER);
	}
	if (newSizeY == 0) {
		newSizeY = mat->sizeY;
	} else if (newSizeY < 0) {
		ThrowException (NEGATIVE_INDEX_OR_SIZE);
	} else if (newSizeY < mat->sizeY) {
		ThrowException (MATRIX_RESIZE_NOT_GREATER);
	}

	if (newSizeX != mat->sizeX) {
		mat->elementMatrix = (void***) realloc (mat->elementMatrix, newSizeX * sizeof (void**) );
	}

	if (newSizeY != mat->sizeY) {
		int i;
		for (i = 0; i < newSizeX; i++) {
			mat->elementMatrix[i] = (void**) realloc (mat->elementMatrix[i], newSizeY * sizeof (void*) );
		}
	}

    long i;
    long j;

	for (i = mat->sizeX; i < newSizeX; i++) {
		for (j = 0; j < newSizeY; j++) {
			mat->elementMatrix[i][j] = 0;
		}
	}

	for (i = 0; i < newSizeX; i++) {
		for (j = mat->sizeY; j < newSizeY; j++) {
			mat->elementMatrix[i][j] = 0;
		}
	}

	mat->sizeX = newSizeX;
	mat->sizeY = newSizeY;

}

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

void* MatrixElement (Matrix* mat, long indexX, long indexY) {

	if (indexX > mat->sizeX - 1 || indexY > mat->sizeY - 1) {
		ThrowException (INDEX_OUT_OF_RANGE_EXCEPTION);
	} else if (indexX < 0 || indexY < 0) {
		ThrowException (NEGATIVE_INDEX_OR_SIZE);
	}

	return mat->elementMatrix[indexX][indexY];
}

/* Method: MatrixSize
 * Parameters:
 * mat - Pointer to the Matrix to be checked.
 * whichSize - Which size to get (x or y)
 * Return value:
 * Returns wether the specified size of the Matrix.
 * Description:
 * Returns mat->size(X | Y).
 */

long MatrixSize (Matrix* mat, char whichSize) {
	switch (whichSize) {
	case 'x': case 'X':
		return mat->sizeX;
		break;
	case 'y': case 'Y':
		return mat->sizeY;
		break;
	default:
		ThrowException (INVALID_METHOD_MODE);
	}
	return 0;
}
