#ifndef PHYSXMATRIX_H_
#define PHYSXMATRIX_H_

#include <btBulletDynamicsCommon.h>

#include <gazengine/math/Matrix.h>

namespace BulletMatrix
{
	btTransform toBtTransform(const Matrix44& original);

	Matrix44 toMatrix44(const btTransform& original);
}

#endif /* PHYSXMATRIX_H_ */
