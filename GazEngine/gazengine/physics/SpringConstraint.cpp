#include <algorithm>
#include <cmath>

#include "../GazEngine.h"
#include "../model/Line2.h"
#include "SpringConstraint.h"

using namespace std;

SpringConstraint::SpringConstraint(float elasticity, Body* bodyA, Body* bodyB) :
	bodyA(bodyA),
	bodyB(bodyB),
	debugModel(NULL),
	elasticity(elasticity),
	restingDistance((bodyB->getPosition() - bodyA->getPosition()).getMagnitude())
{
}

SpringConstraint::SpringConstraint(float elasticity, Body* bodyA, Body* bodyB, float restingDistance) :
	bodyA(bodyA),
	bodyB(bodyB),
	debugModel(NULL),
	elasticity(elasticity),
	restingDistance(restingDistance)
{
}

void SpringConstraint::apply()
{
	// F = -kd
	// where F = force, k = elasticity, d = displacement from resting distance

	Vector2 displacement = bodyB->getPosition() - bodyA->getPosition();
	float displacementMagnitude = displacement.getMagnitude() - restingDistance;
	displacement.normalize();
	displacement *= displacementMagnitude * 0.5f * elasticity;
	if (bodyA->isDynamic())
	{
		bodyA->applyForce(displacement, bodyA->getPosition());
	}

	displacement *= -1.0f;
	if (bodyB->isDynamic())
	{
		bodyB->applyForce(displacement, bodyB->getPosition());
	}

	if (debugModel != NULL)
	{
		float stretchedness = min(restingDistance / abs(displacementMagnitude) / elasticity, 1.0f);
		debugModel->setColour(Vector4(1.0f - stretchedness, 0.0f, stretchedness, 1.0f));
		debugModel->setPointA(bodyA->getPosition());
		debugModel->setPointB(bodyB->getPosition());
	}
}

bool SpringConstraint::isDebugRendered()
{
	return debugModel != NULL;
}

void SpringConstraint::setDebugRendered(bool debugRendered)
{
	if (debugRendered && debugModel == NULL)
	{
		Entity* debugEntity = new Entity;
		debugModel = new Line2(bodyA->getPosition(), bodyB->getPosition());
		debugEntity->addComponent(debugModel);
		debugModel->setEntity(debugEntity);

		GazEngine::addEntity(debugEntity);
	}
	else if (!debugRendered && debugModel != NULL)
	{
		GazEngine::removeEntity(*debugModel->getEntity());
		debugModel = NULL;
	}
}
