#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct _Matrix {
	long sizeX, sizeY;
	void*** elementMatrix;
} Matrix;

void MatrixInit (Matrix* mat, long sizeX, long sizeY);
void MatrixDelete (Matrix* mat);
void MatrixSetElement (Matrix* mat, void* element, long indexX, long indexY);
void MatrixExpand (Matrix* mat, long newSizeX, long newSizeY);
void* MatrixElement (Matrix* mat, long indexX, long indexY);
long MatrixSize (Matrix* mat, char whichSize);

#endif
