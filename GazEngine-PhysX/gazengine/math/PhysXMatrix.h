#ifndef PHYSXMATRIX_H_
#define PHYSXMATRIX_H_

#include <PxPhysicsAPI.h>

#include <gazengine/math/Matrix.h>

namespace PhysXMatrix
{
	physx::PxTransform toPxTransform(const Matrix44& original);

	Matrix44 toMatrix44(const physx::PxTransform& original);
}

#endif /* PHYSXMATRIX_H_ */
