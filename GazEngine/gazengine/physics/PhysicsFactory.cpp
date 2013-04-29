#include "PhysicsFactory.h"

PhysicsFactory* PhysicsFactory::instance = NULL;

PhysicsFactory* PhysicsFactory::getInstance()
{
	return instance;
}

void PhysicsFactory::setInstance(PhysicsFactory* instance)
{
	PhysicsFactory::instance = instance;
}
