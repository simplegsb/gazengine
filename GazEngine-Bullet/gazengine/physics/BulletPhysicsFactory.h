#ifndef BULLETPHYSICSFACTORY_H_
#define BULLETPHYSICSFACTORY_H_

#include <gazengine/physics/PhysicsFactory.h>

class BulletPhysicsFactory : public PhysicsFactory
{
	public:
		Body* createBody(Body::Material material, Model* model, Vector3 position, bool dynamic);
};

#endif /* BULLETPHYSICSFACTORY_H_ */
