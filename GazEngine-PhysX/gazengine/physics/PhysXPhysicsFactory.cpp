#include "PhysxBody.h"
#include "PhysXPhysicsFactory.h"

using namespace physx;

PhysXPhysicsFactory::PhysXPhysicsFactory(PxPhysics* physics) :
	physics(physics)
{
}

Body* PhysXPhysicsFactory::createBody(Body::Material material, Model* model, Vector3 position, bool dynamic)
{
	return new PhysXBody(*physics, material, model, position, dynamic);
}
