#include "PhysXMatrix.h"

using namespace physx;

namespace PhysXMatrix
{
	PxTransform toPxTransform(const Matrix44& original)
	{
		PxMat44 physxMatrix;

		physxMatrix.column0.x = original[0];
		physxMatrix.column0.y = original[1];
		physxMatrix.column0.z = original[2];
		physxMatrix.column0.w = original[3];

		physxMatrix.column1.x = original[4];
		physxMatrix.column1.y = original[5];
		physxMatrix.column1.z = original[6];
		physxMatrix.column1.w = original[7];

		physxMatrix.column2.x = original[8];
		physxMatrix.column2.y = original[9];
		physxMatrix.column2.z = original[10];
		physxMatrix.column2.w = original[11];

		physxMatrix.column3.x = original[12];
		physxMatrix.column3.y = original[13];
		physxMatrix.column3.z = original[14];
		physxMatrix.column3.w = original[15];

		return PxTransform(physxMatrix);
	}

	Matrix44 toMatrix44(const PxTransform& original)
	{
		PxMat44 physxMatrix(original);
		Matrix44 matrix;

		matrix[0] = physxMatrix.column0.x;
		matrix[1] = physxMatrix.column0.y;
		matrix[2] = physxMatrix.column0.z;
		matrix[3] = physxMatrix.column0.w;

		matrix[4] = physxMatrix.column1.x;
		matrix[5] = physxMatrix.column1.y;
		matrix[6] = physxMatrix.column1.z;
		matrix[7] = physxMatrix.column1.w;

		matrix[8] = physxMatrix.column2.x;
		matrix[9] = physxMatrix.column2.y;
		matrix[10] = physxMatrix.column2.z;
		matrix[11] = physxMatrix.column2.w;

		matrix[12] = physxMatrix.column3.x;
		matrix[13] = physxMatrix.column3.y;
		matrix[14] = physxMatrix.column3.z;
		matrix[15] = physxMatrix.column3.w;

		return matrix;
	}
}
