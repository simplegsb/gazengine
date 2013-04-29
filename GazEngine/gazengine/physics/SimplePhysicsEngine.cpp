#include <algorithm>

#include "SimplePhysicsEngine.h"

using namespace std;

SimplePhysicsEngine::SimplePhysicsEngine(const Vector2& gravity) :
	bodies(),
	gravity(gravity),
	integrator(NULL)
{
}

SimplePhysicsEngine::~SimplePhysicsEngine()
{
	if (integrator != NULL)
	{
		delete integrator;
	}
}

void SimplePhysicsEngine::addEntity(Entity* entity)
{
	vector<Body*> entityBodies = entity->getComponents<Body>();
	for (unsigned int index = 0; index < entityBodies.size(); index++)
	{
		bodies.push_back(entityBodies[index]);
	}

	vector<Constraint*> entityConstraints = entity->getComponents<Constraint>();
	for (unsigned int index = 0; index < entityConstraints.size(); index++)
	{
		constraints.push_back(entityConstraints[index]);
	}
}

void SimplePhysicsEngine::advance()
{
	for (unsigned int index = 0; index < bodies.size(); index++)
	{
		if (bodies[index]->isDynamic())
		{
			bodies[index]->applyForce(gravity, bodies[index]->getPosition());
			//bodies[index]->applyForce(gravity * bodies[index]->getMass(), bodies[index]->getPosition());
			integrator->integrate(*bodies[index]);
		}
	}

	for (unsigned int index = 0; index < constraints.size(); index++)
	{
		constraints[index]->apply();
	}
}

void SimplePhysicsEngine::destroy()
{
}

const Integrator* SimplePhysicsEngine::getIntegrator() const
{
	return integrator;
}

void SimplePhysicsEngine::init()
{
}

void SimplePhysicsEngine::removeEntity(const Entity& entity)
{
	vector<Body*> entityBodies = entity.getComponents<Body>();
	for (unsigned int index = 0; index < entityBodies.size(); index++)
	{
		bodies.erase(remove(bodies.begin(), bodies.end(), entityBodies[index]));
	}

	vector<Constraint*> entityConstraints = entity.getComponents<Constraint>();
	for (unsigned int index = 0; index < entityConstraints.size(); index++)
	{
		constraints.erase(remove(constraints.begin(), constraints.end(), entityConstraints[index]));
	}
}

void SimplePhysicsEngine::setIntegrator(Integrator* integrator)
{
	this->integrator = integrator;
}
