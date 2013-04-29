#ifndef FREEGLUTENGINE_H_
#define FREEGLUTENGINE_H_

#include <gazengine/engine/Engine.h>

class FreeGLUTEngine : public Engine
{
	public:
		FreeGLUTEngine(const std::string& title, int width, int height);

		void addEntity(Entity* entity);

		void advance();

		void destroy();

		int getHeight() const;

		int getWidth() const;

		void init();

		void removeEntity(const Entity& entity);

	private:
		int height;

		std::string title;

		int width;
};

#endif /* FREEGLUTENGINE_H_ */
