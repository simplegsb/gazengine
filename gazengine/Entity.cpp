#include <algorithm>

#include "Component.h"
#include "Entity.h"

using namespace std;

unsigned int Entity::nextId = 0;

Entity::Entity(unsigned short category, const std::string& name) :
		category(category),
		components(),
		id(nextId++),
		name(name)
{
}

Entity::~Entity()
{
	for (unsigned int index = 0; index < components.size(); index++)
	{
		delete components[index];
	}
}

void Entity::addComponent(Component* component)
{
	components.push_back(component);
}

unsigned short Entity::getCategory() const
{
	return category;
}

unsigned int Entity::getId() const
{
	return id;
}

const string& Entity::getName() const
{
	return name;
}

void Entity::removeComponent(const Component& component)
{
	vector<Component*>::iterator componentIter = find(components.begin(), components.end(), &component);
	if (componentIter != components.end())
	{
		components.erase(componentIter);
	}
}
