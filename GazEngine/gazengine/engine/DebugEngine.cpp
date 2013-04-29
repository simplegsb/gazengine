#include "DebugEngine.h"

DebugEngine::DebugEngine(Engine* engine) :
	engine(engine), timer()
{
}

DebugEngine::~DebugEngine()
{
	delete engine;
}

void DebugEngine::advance()
{
	timer.reset();

	engine->advance();

	timer.tick();
}

void DebugEngine::destroy()
{
	engine->destroy();
}

float DebugEngine::getAdvanceTime() const
{
	return timer.getDeltaTime();
}

void DebugEngine::init()
{
	engine->init();
}
