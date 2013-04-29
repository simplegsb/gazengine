#ifndef PHYSXVECTOR_H_
#define PHYSXVECTOR_H_

#include <PxPhysicsAPI.h>

#include <gazengine/math/Vector.h>

namespace PhysXVector
{
	physx::PxVec3 toPxVec3(const Vector3& original);

	Vector3 toVector3(const physx::PxVec3& original);
}

#endif /* PHYSXVECTOR_H_ */
