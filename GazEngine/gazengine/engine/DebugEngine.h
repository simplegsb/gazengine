#ifndef DEBUGENGINE_H_
#define DEBUGENGINE_H_

#include "../model/Text.h"
#include "../Timer.h"
#include "Engine.h"

class DebugEngine : public Engine
{
	public:
		DebugEngine(Engine* engine);

		virtual ~DebugEngine();

		void addEntity(Entity* entity);

		void advance();

		void destroy();

		float getAdvanceTime() const;

		Text* getDebugText();

		const Text* getDebugText() const;

		void init();

		void removeEntity(const Entity& entity);

		void restart();

	private:
		float advanceCount;

		Timer advanceTimer;

		Text* debugText;

		Engine* engine;

		Timer outputTimer;
};

#endif /* DEBUGENGINE_H_ */
