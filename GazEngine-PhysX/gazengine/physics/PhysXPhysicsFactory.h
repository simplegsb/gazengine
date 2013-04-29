#ifndef PHYSXPHYSICSFACTORY_H_
#define PHYSXPHYSICSFACTORY_H_

#include <PxPhysicsAPI.h>

#include <gazengine/physics/PhysicsFactory.h>

#include "PhysXFixedConstraint.h"

class PhysXPhysicsFactory : public PhysicsFactory
{
	public:
		PhysXPhysicsFactory(physx::PxPhysics* physics, physx::PxCooking* cooking);

		Body* createBody(const Body::Material& material, Model* model, const Matrix44& transformation, bool dynamic);

		Body* createBody(const Body::Material& material, const std::vector<const Model*>& models,
			const Matrix44& transformation, bool dynamic);

		PhysXFixedConstraint* createFixedConstraint(PhysXBody* bodyA, PhysXBody* bodyB,
			const Matrix44& transformation);

		// TODO Remove this and replace with proper joint factories!!!
		physx::PxPhysics* getPhysics();

	private:
		physx::PxCooking* cooking;

		physx::PxPhysics* physics;
};

#endif /* PHYSXPHYSICSFACTORY_H_ */
