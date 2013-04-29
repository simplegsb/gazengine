#ifndef ENGINE_H_
#define ENGINE_H_

#include "../Entity.h"

class Engine
{
	public:
		virtual ~Engine()
		{
		}

		virtual void addEntity(Entity* entity) = 0;

		virtual void advance() = 0;

		virtual void destroy() = 0;

		virtual void init() = 0;

		virtual void removeEntity(const Entity& entity) = 0;
};

#endif /* ENGINE_H_ */
