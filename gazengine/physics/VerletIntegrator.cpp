#include <cmath>

#include "../GazEngine.h"
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
		previousPositions[&body] = body.getPosition();
	}

	Vector2 newPosition = body.getPosition() * (1 + damping) - previousPositions[&body] * damping +
		body.getLinearAcceleration() * pow(GazEngine::getDeltaTime() * 2.0f, 2.0f); // Delta is doubled to speed up sim!!!

	previousPositions[&body] = body.getPosition();
	body.setPosition(newPosition);
	body.clearForces();
}
