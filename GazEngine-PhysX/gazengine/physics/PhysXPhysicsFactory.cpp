#include "PhysXBody.h"
#include "PhysXPhysicsFactory.h"

using namespace physx;

PhysXPhysicsFactory::PhysXPhysicsFactory(PxPhysics* physics, PxCooking* cooking) :
	cooking(cooking),
	physics(physics)
{
}

Body* PhysXPhysicsFactory::createBody(const Body::Material& material, Model* model, const Matrix44& transformation,
									  bool dynamic)
{
	return new PhysXBody(*physics, *cooking, material, model, transformation, dynamic);
}

Body* PhysXPhysicsFactory::createBody(const Body::Material& material, const std::vector<const Model*>& models,
									  const Matrix44& transformation, bool dynamic)
{
	return new PhysXBody(*physics, *cooking, material, models, transformation, dynamic);
}

PhysXFixedConstraint* PhysXPhysicsFactory::createFixedConstraint(PhysXBody* bodyA, PhysXBody* bodyB,
			const Matrix44& transformation)
{
	return new PhysXFixedConstraint(*physics, bodyA, bodyB, transformation);
}

physx::PxPhysics* PhysXPhysicsFactory::getPhysics()
{
	return physics;
}
