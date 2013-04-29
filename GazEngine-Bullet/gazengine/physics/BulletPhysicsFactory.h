#ifndef BULLETPHYSICSFACTORY_H_
#define BULLETPHYSICSFACTORY_H_

#include <gazengine/physics/PhysicsFactory.h>

class BulletPhysicsFactory : public PhysicsFactory
{
	public:
		Body* createBody(const Body::Material& material, Model* model, const Matrix44& transformation, bool dynamic);
};

#endif /* BULLETPHYSICSFACTORY_H_ */
