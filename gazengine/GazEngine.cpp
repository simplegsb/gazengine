#include <vector>

#include "GazEngine.h"

using namespace std;

namespace GazEngine
{
	vector<Engine*> engines;
	bool initialised = false;
	bool paused = false;
	bool stopped = false;

	void addEngine(Engine* engine)
	{
		engines.push_back(engine);
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
			for (unsigned int index = 0; index < engines.size(); index++)
			{
				engines.at(index)->init();
			}

			initialised = true;
		}

		while (!paused && !stopped)
		{
			for (unsigned int index = 0; index < engines.size(); index++)
			{
				engines.at(index)->advance();
			}
		}

		if (stopped)
		{
			for (unsigned int index = 0; index < engines.size(); index++)
			{
				engines.at(index)->destroy();
				delete engines.at(index);
			}
		}
	}

	void stop()
	{
		stopped = true;
	}
}
