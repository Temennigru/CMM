#include <stdlib.h>
#include "list.h"
#include "exception.h"
#include "matrix.h"

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

void MatrixSetElement (Matrix* mat, void* element, long indexX, long indexY) {
	if (indexX > mat->sizeX - 1 || indexY > mat->sizeY - 1) {
		ThrowException (INDEX_OUT_OF_RANGE_EXCEPTION);
	} else if (indexX < 0 || indexY < 0) {
		ThrowException (NEGATIVE_INDEX_OR_SIZE);
	}

	mat->elementMatrix[indexX][indexY] = element;
}

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

void* MatrixElement (Matrix* mat, long indexX, long indexY) {

	if (indexX > mat->sizeX - 1 || indexY > mat->sizeY - 1) {
		ThrowException (INDEX_OUT_OF_RANGE_EXCEPTION);
	} else if (indexX < 0 || indexY < 0) {
		ThrowException (NEGATIVE_INDEX_OR_SIZE);
	}

	return mat->elementMatrix[indexX][indexY];
}

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
