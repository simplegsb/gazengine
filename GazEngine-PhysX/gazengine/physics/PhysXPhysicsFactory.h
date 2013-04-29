#ifndef PHYSXPHYSICSFACTORY_H_
#define PHYSXPHYSICSFACTORY_H_

#include <PxPhysicsAPI.h>

#include <gazengine/physics/PhysicsFactory.h>

class PhysXPhysicsFactory : public PhysicsFactory
{
	public:
		PhysXPhysicsFactory(physx::PxPhysics* physics, physx::PxCooking* cooking);

		Body* createBody(const Body::Material& material, Model* model, const Matrix44& transformation, bool dynamic);

	private:
		physx::PxCooking* cooking;

		physx::PxPhysics* physics;
};

#endif /* PHYSXPHYSICSFACTORY_H_ */
