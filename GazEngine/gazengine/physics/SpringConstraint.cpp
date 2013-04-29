#include <algorithm>
#include <cmath>

#include "../GazEngine.h"
#include "../math/MathFunctions.h"
#include "../model/Line2.h"
#include "SpringConstraint.h"

using namespace std;

SpringConstraint::SpringConstraint(float elasticity, Body* bodyA, Body* bodyB) :
	bodyA(bodyA),
	bodyB(bodyB),
	debugModel(NULL),
	elasticity(elasticity),
	restingDistance((getTranslation3(bodyB->getTransformation()) -
		getTranslation3(bodyA->getTransformation())).getMagnitude())
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

	Vector3 displacement = getTranslation3(bodyB->getTransformation()) - getTranslation3(bodyA->getTransformation());
	float displacementMagnitude = displacement.getMagnitude() - restingDistance;
	displacement.normalize();
	displacement *= displacementMagnitude * 0.5f * elasticity;
	if (bodyA->isDynamic())
	{
		bodyA->applyForce(displacement, getTranslation3(bodyA->getTransformation()));
	}

	displacement *= -1.0f;
	if (bodyB->isDynamic())
	{
		bodyB->applyForce(displacement, getTranslation3(bodyB->getTransformation()));
	}

	if (debugModel != NULL)
	{
		float stretchedness = min(restingDistance / abs(displacementMagnitude) / elasticity, 1.0f);
		debugModel->setColour(Vector4(1.0f - stretchedness, 0.0f, stretchedness, 1.0f));
		// TODO
		//debugModel->setPointA(getTranslation3(bodyA->getTransformation()));
		//debugModel->setPointB(getTranslation3(bodyB->getTransformation()));
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
		// TODO
		//debugModel = new Line2(bodyA->getPosition(), bodyB->getPosition());
		//debugEntity->addComponent(debugModel);
		//debugModel->setEntity(debugEntity);

		GazEngine::addEntity(debugEntity);
	}
	else if (!debugRendered && debugModel != NULL)
	{
		GazEngine::removeEntity(*debugModel->getEntity());
		debugModel = NULL;
	}
}
