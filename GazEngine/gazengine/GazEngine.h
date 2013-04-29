#ifndef GAZENGINE_H_
#define GAZENGINE_H_

#include "engine/Engine.h"
#include "graph/SimpleTree.h"

namespace GazEngine
{
	void addEngine(Engine* engine);

	void addEntity(Entity* entity);

	void addToWorld(SimpleTree* node);

	void addWorldRepresentation(SimpleTree* tree);

	const std::vector<Entity*> getAllEntities();

	float getDeltaTime();

	unsigned short getMaxFrameRate();

	float getTotalTime();

	const std::vector<SimpleTree*> getWorldRepresentations();

	void pause();

	void play();

	void removeAllEntities(bool deleteEntities = true);

	void removeEngine(const Engine& engine);

	void removeEntity(const Entity& entity, bool deleteEntity = true);

	void setMaxFrameRate(unsigned short maxFrameRate);

	void stop();
}

#endif /* GAZENGINE_H_ */
