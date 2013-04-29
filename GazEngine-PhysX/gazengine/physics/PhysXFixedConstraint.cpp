#include <gazengine/math/MathFunctions.h>

#include "../math/PhysXMatrix.h"
#include "PhysXFixedConstraint.h"

using namespace physx;

PhysXFixedConstraint::PhysXFixedConstraint(PxPhysics& physics, PhysXBody* bodyA, PhysXBody* bodyB,
		const Matrix44& transformation) :
	joint(NULL)
{
	Matrix44 bodyARelative = transformation;
	Matrix44 bodyAWorld = PhysXMatrix::toMatrix44(static_cast<PxRigidActor*>(bodyA->getActor())->getGlobalPose());
	getTranslation3(bodyARelative) -= getTranslation3(bodyAWorld);

	Matrix44 bodyBRelative = transformation;
	Matrix44 bodyBWorld = PhysXMatrix::toMatrix44(static_cast<PxRigidActor*>(bodyB->getActor())->getGlobalPose());
	getTranslation3(bodyBRelative) -= getTranslation3(bodyBWorld);

	joint = PxFixedJointCreate(physics, static_cast<PxRigidActor*>(bodyA->getActor()),
		PhysXMatrix::toPxTransform(bodyARelative), static_cast<PxRigidActor*>(bodyB->getActor()),
		PhysXMatrix::toPxTransform(bodyBRelative));

	// Aaargh! Get rid of me!
	joint->setBreakForce(100000.0f, 100000.0f);
}

PhysXFixedConstraint::~PhysXFixedConstraint()
{
	if (joint != NULL)
	{
		joint->release();
	}
}

void PhysXFixedConstraint::apply()
{
}
