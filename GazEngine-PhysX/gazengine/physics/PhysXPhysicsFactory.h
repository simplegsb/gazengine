#ifndef PHYSXPHYSICSFACTORY_H_
#define PHYSXPHYSICSFACTORY_H_

#include <PxPhysicsAPI.h>

#include <gazengine/physics/PhysicsFactory.h>

class PhysXPhysicsFactory : public PhysicsFactory
{
	public:
		PhysXPhysicsFactory(physx::PxPhysics* physics);

		Body* createBody(Body::Material material, Model* model, Vector3 position, bool dynamic);

	private:
		physx::PxPhysics* physics;
};

#endif /* PHYSXPHYSICSFACTORY_H_ */
