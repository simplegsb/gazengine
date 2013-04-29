#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "Entity.h"

class Component
{
	public:
		Component();

		virtual ~Component();

		Entity* getEntity();

		const Entity* getEntity() const;

		void setEntity(Entity* entity);

	private:
		Entity* entity;
};

#endif /* COMPONENT_H_ */
