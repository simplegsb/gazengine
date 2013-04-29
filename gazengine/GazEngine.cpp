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
	void removePendingEntities();

	vector<Engine*> engines;
	vector<Entity*> entities;
	vector<Entity*> entitiesToBeAdded;
	vector<const Entity*> entitiesToBeRemoved;
	Timer frameTimer;
	bool initialised = false;
	unsigned short maxFrameRate = 0;
	bool paused = false;
	bool stopped = false;
	Timer timer;

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

			addPendingEntities();
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

	void removeEntity(const Entity& entity)
	{
		entitiesToBeRemoved.push_back(&entity);
	}

	void removePendingEntities()
	{
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
				delete *entityIter;
				entities.erase(entityIter);
			}
		}
		entitiesToBeRemoved.clear();
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
