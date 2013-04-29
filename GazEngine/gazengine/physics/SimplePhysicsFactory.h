#ifndef SIMPLEPHYSICSFACTORY_H_
#define SIMPLEPHYSICSFACTORY_H_

#include <gazengine/physics/PhysicsFactory.h>

class SimplePhysicsFactory : public PhysicsFactory
{
	public:
		Body* createBody(Body::Material material, Model* model, Vector3 position, bool dynamic);
};

#endif /* SIMPLEPHYSICSFACTORY_H_ */
