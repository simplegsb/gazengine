#ifndef DEBUGENGINE_H_
#define DEBUGENGINE_H_

#include "../Timer.h"
#include "Engine.h"

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
