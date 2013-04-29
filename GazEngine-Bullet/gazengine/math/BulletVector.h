#ifndef BULLETVECTOR_H_
#define BULLETVECTOR_H_

#include <btBulletDynamicsCommon.h>

#include <gazengine/math/Vector.h>

namespace BulletVector
{
	btVector3 toBtVector3(const Vector3& original);

	Vector3 toVector3(const btVector3& original);
}

#endif /* BULLETVECTOR_H_ */
