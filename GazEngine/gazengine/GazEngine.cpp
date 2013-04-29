#include <algorithm>
#include <vector>

#include <windows.h>

#include "Events.h"
#include "GazEngine.h"
#include "Timer.h"

using namespace std;

namespace GazEngine
{
	void addPendingEntities();
	void removeModel(SimpleTree* node, const Model& model);
	void removePendingEntities();

	vector<Engine*> engines;
	vector<Entity*> entities;
	vector<Entity*> entitiesToBeAdded;
	vector<const Entity*> entitiesToBeDeleted;
	vector<const Entity*> entitiesToBeRemoved;
	Timer frameTimer;
	bool initialised = false;
	unsigned short maxFrameRate = 0;
	bool paused = false;
	bool stopped = false;
	Timer timer;
	vector<SimpleTree*> worldRepresentations;

	void addEngine(Engine* engine)
	{
		engines.push_back(engine);

		if (initialised)
		{
			engine->init();
		}
	}

	void addEntity(Entity* entity)
	{
		entitiesToBeAdded.push_back(entity);
	}

	void addPendingEntities()
	{
		for (unsigned int entityIndex = 0; entityIndex < entitiesToBeAdded.size(); entityIndex++)
		{
			for (unsigned int engineIndex = 0; engineIndex < engines.size(); engineIndex++)
			{
				engines[engineIndex]->addEntity(entitiesToBeAdded[entityIndex]);
			}
			entities.push_back(entitiesToBeAdded[entityIndex]);
		}
		entitiesToBeAdded.clear();
	}

	void addToWorld(SimpleTree* node)
	{
		for (unsigned int index = 0; index < worldRepresentations.size(); index++)
		{
			worldRepresentations[index]->addChild(node);
		}
	}

	void addWorldRepresentation(SimpleTree* tree)
	{
		worldRepresentations.push_back(tree);
	}

	const vector<Entity*> getAllEntities()
	{
		return entities;
	}

	float getDeltaTime()
	{
		return timer.getDeltaTime();
	}

	unsigned short getMaxFrameRate()
	{
		return maxFrameRate;
	}

	float getTotalTime()
	{
		return timer.getGameTime();
	}

	const vector<SimpleTree*> getWorldRepresentations()
	{
		return worldRepresentations;
	}

	void pause()
	{
		paused = true;
	}

	void play()
	{
		if (stopped)
		{
			return;
		}

		paused = false;

		if (!initialised)
		{
			timer.reset();

			for (unsigned int index = 0; index < engines.size(); index++)
			{
				engines[index]->init();
			}

			initialised = true;
		}

		while (!paused && !stopped)
		{
			timer.tick();
			if (maxFrameRate != 0)
			{
				frameTimer.reset();
			}

			addPendingEntities();
			for (unsigned int index = 0; index < engines.size(); index++)
			{
				engines[index]->advance();
			}
			removePendingEntities();

			if (maxFrameRate != 0)
			{
				frameTimer.tick();
				float sleepTime = 1.0f / maxFrameRate - frameTimer.getDeltaTime();
				sleepTime *= 1000.0f;
				if (sleepTime > 0.0f)
				{
					Sleep(static_cast<DWORD>(sleepTime));
				}
			}
		}

		if (stopped)
		{
			// TODO This should happen after engine deletion I think but
			// it is a quick fix to keep RakNet happy (deletes
			// NetworkIDObjects) before shutting down the peer.
			for (unsigned int index = 0; index < entities.size(); index++)
			{
				delete entities[index];
			}

			for (unsigned int index = 0; index < engines.size(); index++)
			{
				engines[index]->destroy();
				delete engines[index];
			}

			for (unsigned int index = 0; index < worldRepresentations.size(); index++)
			{
				delete worldRepresentations[index];
			}
		}
	}

	void removeAllEntities(bool deleteEntities)
	{
		for (unsigned int index = 0; index < entities.size(); index++)
		{
			removeEntity(*entities[index], deleteEntities);
		}
	}

	void removeEngine(const Engine& engine)
	{
		vector<Engine*>::iterator engineIter = find(engines.begin(), engines.end(), &engine);
		if (engineIter != engines.end())
		{
			engines.erase(engineIter);
			delete &engine;
		}
	}

	void removeEntity(const Entity& entity, bool deleteEntity)
	{
		entitiesToBeRemoved.push_back(&entity);

		if (deleteEntity)
		{
			entitiesToBeDeleted.push_back(&entity);
		}
	}

	void removeModel(SimpleTree* node, const Model& model)
	{
		if (node->getModel() == &model)
		{
			node->setModel(NULL);
		}

		for (unsigned int index = 0; index < node->getChildren().size(); index++)
		{
			removeModel(node->getChildren()[index], model);
		}
	}

	void removePendingEntities()
	{
		for (unsigned int entityIndex = 0; entityIndex < entitiesToBeRemoved.size(); entityIndex++)
		{
			for (unsigned int entityIndex2 = entityIndex + 1; entityIndex2 < entitiesToBeRemoved.size(); entityIndex2++)
			{
				if (entitiesToBeRemoved[entityIndex] == entitiesToBeRemoved[entityIndex2])
				{
					int i = 0;
					i++;
				}
			}
		}

		for (unsigned int entityIndex = 0; entityIndex < entitiesToBeRemoved.size(); entityIndex++)
		{
			vector<Entity*>::iterator entityIter = find(entities.begin(),
				entities.end(), entitiesToBeRemoved[entityIndex]);
			if (entityIter != entities.end())
			{
				for (unsigned int engineIndex = 0; engineIndex < engines.size(); engineIndex++)
				{
					engines[engineIndex]->removeEntity(**entityIter);
				}

				vector<Model*> models = (*entityIter)->getComponents<Model>();
				for (unsigned int modelIndex = 0; modelIndex < models.size(); modelIndex++)
				{
					for (unsigned int worldIndex = 0; worldIndex < worldRepresentations.size(); worldIndex++)
					{
						removeModel(worldRepresentations[worldIndex], *models[modelIndex]);
					}
				}

				entities.erase(entityIter);
			}
		}
		entitiesToBeRemoved.clear();

		for (unsigned int index = 0; index < entitiesToBeDeleted.size(); index++)
		{
			delete entitiesToBeDeleted[index];
		}
		entitiesToBeDeleted.clear();
	}

	void setMaxFrameRate(unsigned short maxFrameRate)
	{
		GazEngine::maxFrameRate = maxFrameRate;
	}

	void stop()
	{
		stopped = true;
	}
}
