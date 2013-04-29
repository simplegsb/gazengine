#ifndef SIMPLEPHYSICSFACTORY_H_
#define SIMPLEPHYSICSFACTORY_H_

#include <gazengine/physics/PhysicsFactory.h>

class SimplePhysicsFactory : public PhysicsFactory
{
	public:
		Body* createBody(const Body::Material& material, Model* model, const Matrix44& transformation, bool dynamic);
};

#endif /* SIMPLEPHYSICSFACTORY_H_ */
