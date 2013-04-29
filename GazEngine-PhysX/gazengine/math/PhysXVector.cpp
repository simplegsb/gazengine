#include "PhysXVector.h"

using namespace physx;

namespace PhysXVector
{
	PxVec3 toPxVec3(const Vector3& original)
	{
		return PxVec3(original.X(), original.Y(), original.Z());
	}

	Vector3 toVector3(const PxVec3& original)
	{
		return Vector3(original.x, original.y, original.z);
	}
}
