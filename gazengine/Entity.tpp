#include "Entity.h"

template<typename ComponentType>
std::vector<ComponentType*> Entity::getComponents() const
{
	std::vector<ComponentType*> typedComponents;

	for (unsigned int index = 0; index < components.size(); index++)
	{
		ComponentType* component = dynamic_cast<ComponentType*>(components.at(index));
		if (component != NULL)
		{
			typedComponents.push_back(component);
		}
	}

	return typedComponents;
}

template<typename ComponentType>
ComponentType* Entity::getSingleComponent() const
{
	for (unsigned int index = 0; index < components.size(); index++)
	{
		ComponentType* component = dynamic_cast<ComponentType*>(components.at(index));
		if (component != NULL)
		{
			return component;
		}
	}

	return NULL;
}
