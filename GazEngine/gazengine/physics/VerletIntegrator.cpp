#include <cmath>

#include "../GazEngine.h"
#include "../math/MathFunctions.h"
#include "VerletIntegrator.h"

VerletIntegrator::VerletIntegrator(float damping) :
	damping(damping),
	previousPositions()
{
}

void VerletIntegrator::integrate(Body& body)
{
	if (previousPositions.find(&body) == previousPositions.end())
	{
		previousPositions[&body] = getTranslation3(body.getTransformation());
	}

	Vector3 newPosition = getTranslation3(body.getTransformation()) * (1 + damping) - previousPositions[&body] * damping +
		body.getLinearAcceleration() * pow(GazEngine::getDeltaTime() * 2.0f, 2.0f); // Delta is doubled to speed up sim!!!

	previousPositions[&body] = getTranslation3(body.getTransformation());
	setTranslation(body.getTransformation(), newPosition);
	body.clearForces();
}
