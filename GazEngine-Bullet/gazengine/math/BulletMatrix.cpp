#include "BulletMatrix.h"

namespace BulletMatrix
{
	btTransform toBtTransform(const Matrix44& original)
	{
		btTransform transform;
		transform.setFromOpenGLMatrix(original.getData());

		return transform;
	}

	Matrix44 toMatrix44(const btTransform& original)
	{
		Matrix44 matrix;
		original.getOpenGLMatrix(matrix.getData());

		return matrix;
	}
}
