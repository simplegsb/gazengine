#pragma once

#include "Body.h"
#include "Constraint.h"

class SpringConstraint : public Constraint
{
	public:
		SpringConstraint(float elasticity, Body* bodyA, Body* bodyB);

		SpringConstraint(float elasticity, Body* bodyA, Body* bodyB, float restingDistance);

		void apply();

		bool isDebugRendered();

		void setDebugRendered(bool debugRendered);

	private:
		Body* bodyA;

		Body* bodyB;

		Line2* debugModel;

		float elasticity;

		float restingDistance;
};
