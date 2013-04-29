#ifndef GAZENGINE_H_
#define GAZENGINE_H_

#include "engine/Engine.h"
#include "graph/SimpleTree.h"

namespace GazEngine
{
	void addEngine(Engine* engine);

	void addEntity(Entity* entity);

	void addWorldRepresentation(SimpleTree* tree);

	float getDeltaTime();

	unsigned short getMaxFrameRate();

	float getTotalTime();

	void pause();

	void play();

	void removeAllEntities(bool deleteEntities = true);

	void removeEngine(const Engine& engine);

	void removeEntity(const Entity& entity, bool deleteEntity = true);

	void setMaxFrameRate(unsigned short maxFrameRate);

	void stop();
}

#endif /* GAZENGINE_H_ */
