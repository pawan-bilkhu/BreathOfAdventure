#include "Transformation.h"

 Matrix2D BuildMatrix(int rows, int cols)
{
	Matrix2D M;
	//allocation of a two-dimensional array of doubles
	double **f;

	int i = 0, j = 0;
	
	f = new double * [rows];

	for(; i < rows; ++i)
		*(f+i) = new double[cols];

	for(i = 0;i < rows;i++)
		for(j = 0;j < cols; j++)
			f[i][j] = 0;
				
	M.rows = rows;
	M.cols = cols;
	M.Body = f;

	return M;
}

void FreeMatrix( Matrix2D M)
{
	int i;

	for(i=0;i<M.rows;i++)
		delete [] M.Body[i];

	delete [] M.Body;
}

 Matrix2D MatMul( Matrix2D M1,  Matrix2D M2)
{
	 Matrix2D M;
	int i,j,k;
	
	M = BuildMatrix(M1.rows,M2.cols);

	M.rows = M1.rows;
	M.cols = M2.cols;


	for(i = 0; i < M1.rows; i++)
		for(j = 0; j < M2.cols; j++)
			for(k = 0; k < M1.cols; k++)
                M.Body[i][j] += M1.Body[i][k]*M2.Body[k][j];
	return M;
}


Matrix2D GetRotationMatrixAroundOrigin(double angle)
{
	Matrix2D R;
	angle = angle*3.14159265/180;
	R = BuildMatrix(3,3);
	R.Body[0][0] = cos(angle);
	R.Body[0][1] = -sin(angle);
	R.Body[0][2] = 0;
	R.Body[1][0] = sin(angle);
	R.Body[1][1] = cos(angle);
	R.Body[1][2] = 0;
	R.Body[2][0] = 0;
	R.Body[2][1] = 0;
	R.Body[2][2] = 1;

	return R;
}

Matrix2D GetTranslationMatrix(Vector2D V)
{
	Matrix2D T;
	T = BuildMatrix(3,3);
	T.Body[0][0] = 1;
	T.Body[1][1] = 1;
	T.Body[2][2] = 1;
	T.Body[0][2] = V.x;
	T.Body[1][2] = V.y;

	return T;
}

// RJS 2/10/2010
Matrix2D GetArbitraryRotationMatrix(Point2D P, double angle)
{
	Vector2D V, V_opp;

	V.x = P.x;
	V.y = P.y;

	V_opp.x = -V.x;
	V_opp.y = -V.y;

	Matrix2D transToOrigin, rotation, transFromOrigin;
	
	transToOrigin   = GetTranslationMatrix(V_opp);
	rotation        = GetRotationMatrixAroundOrigin(angle);
	transFromOrigin = GetTranslationMatrix(V);

	Matrix2D mul1 = MatMul( rotation, transToOrigin );
	Matrix2D mul2 = MatMul( transFromOrigin, mul1 );


	FreeMatrix(transToOrigin);
	FreeMatrix(rotation);
	FreeMatrix(transFromOrigin);
	FreeMatrix(mul1);

	return mul2;
}


Point2D TransformPoint(Matrix2D M, Point2D P)
{
	double x,y;
	x = P.x;
	y = P.y;

	P.x = M.Body[0][0]*x + M.Body[0][1]*y + M.Body[0][2];  // affine
	P.y = M.Body[1][0]*x + M.Body[1][1]*y + M.Body[1][2];  // affine

	return P;
}

