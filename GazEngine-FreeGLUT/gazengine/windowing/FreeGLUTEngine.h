#ifndef FREEGLUTENGINE_H_
#define FREEGLUTENGINE_H_

#include <gazengine/engine/Engine.h>

class FreeGLUTEngine : public Engine
{
	public:
		FreeGLUTEngine(const std::string& title);

		void addEntity(Entity* entity);

		void advance();

		void destroy();

		void init();

		void removeEntity(const Entity& entity);

	private:
		std::string title;
};

#endif /* FREEGLUTENGINE_H_ */
