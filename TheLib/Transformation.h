#include <stdlib.h>
#include "Collision.h"


struct Matrix2D
{
	int rows;
	int cols;
	double ** Body;
};

Matrix2D BuildMatrix(int rows, int columns);
void FreeMatrix(Matrix2D M);