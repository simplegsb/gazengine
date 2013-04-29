#ifndef DEBUGENGINE_H_
#define DEBUGENGINE_H_

#include "Engine.h"
#include "Timer.h"

class DebugEngine : public Engine
{
	public:
		DebugEngine(Engine* engine);

		virtual ~DebugEngine();

		void advance();

		void destroy();

		float getAdvanceTime() const;

		void init();

	private:
		Engine* engine;

		Timer timer;
};

#endif /* DEBUGENGINE_H_ */
