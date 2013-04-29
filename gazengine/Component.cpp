#include "Component.h"

Component::Component() :
	entity(NULL)
{
}

Component::~Component()
{
}

const Entity* Component::getEntity() const
{
	return entity;
}

void Component::setEntity(Entity* entity)
{
	this->entity = entity;
}
