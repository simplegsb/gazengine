#ifndef GAZENGINE_H_
#define GAZENGINE_H_

#include "engine/Engine.h"

namespace GazEngine
{
	void addEngine(Engine* engine);

	void addEntity(Entity* entity);

	float getDeltaTime();

	unsigned short getMaxFrameRate();

	float getTotalTime();

	void pause();

	void play();

	void removeEngine(const Engine& engine);

	void removeEntity(const Entity& entity);

	void setMaxFrameRate(unsigned short maxFrameRate);

	void stop();
}

#endif /* GAZENGINE_H_ */
