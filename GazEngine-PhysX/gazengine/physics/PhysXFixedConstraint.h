#ifndef PHYSXFIXEDCONSTRAINT_H_
#define PHYSXFIXEDCONSTRAINT_H_

#include <gazengine/physics/Constraint.h>

#include "PhysXBody.h"

class PhysXFixedConstraint : public Constraint
{
	public:
		PhysXFixedConstraint(physx::PxPhysics& physics, PhysXBody* bodyA, PhysXBody* bodyB,
			const Matrix44& transformation);

		~PhysXFixedConstraint();

		void apply();

	private:
		physx::PxJoint* joint;
};

#endif /* PHYSXFIXEDCONSTRAINT_H_ */
