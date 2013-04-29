#include "BulletVector.h"

namespace BulletVector
{
	btVector3 toBtVector3(const Vector3& original)
	{
		return btVector3(original.X(), original.Y(), original.Z());
	}

	Vector3 toVector3(const btVector3& original)
	{
		return Vector3(original.getX(), original.getY(), original.getZ());
	}
}
