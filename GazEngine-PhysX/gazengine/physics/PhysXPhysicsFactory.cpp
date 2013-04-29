#include "PhysxBody.h"
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
