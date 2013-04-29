#include <sstream>

#include "../GazEngine.h"
#include "../math/MathFunctions.h"
#include "DebugEngine.h"

DebugEngine::DebugEngine() :
	advanceCount(0.0f),
	advanceTimer(),
	debugText(NULL),
	engine(NULL),
	outputTimer()
{
	restart();
}

DebugEngine::DebugEngine(Engine* engine) :
	advanceCount(0.0f),
	advanceTimer(),
	debugText(NULL),
	engine(engine),
	outputTimer()
{
	restart();
}

DebugEngine::~DebugEngine()
{
	if (engine != NULL)
	{
		delete engine;
	}
}

void DebugEngine::addEntity(Entity* /*entity*/)
{
}

void DebugEngine::advance()
{
	advanceTimer.reset();

	if (engine != NULL)
	{
		engine->advance();
	}
	advanceCount++;

	advanceTimer.tick();

	outputTimer.tick();
	if (outputTimer.getGameTime() > 1.0f)
	{
		stringstream text;
		text << "Debug info: FPS: ";
		text << (advanceCount / outputTimer.getGameTime());
		debugText->setText(text.str());

		advanceCount = 0.0f;
		outputTimer.reset();
	}
}

void DebugEngine::destroy()
{
	GazEngine::addEntity(debugText->getEntity());

	if (engine != NULL)
	{
		engine->destroy();
	}
}

float DebugEngine::getAdvanceTime() const
{
	return advanceTimer.getDeltaTime();
}

Text* DebugEngine::getDebugText()
{
	return debugText;
}

const Text* DebugEngine::getDebugText() const
{
	return debugText;
}

void DebugEngine::init()
{
	if (engine != NULL)
	{
		engine->init();
	}

	outputTimer.reset();

	SimpleTree* node = new SimpleTree;
	node->setModel(debugText);
	setTranslation(node->getTransformation(), Vector3(-1.0f, 0.75f, -1.0f));
	GazEngine::addToWorld(node);
}

void DebugEngine::removeEntity(const Entity& /*entity*/)
{
}

void DebugEngine::restart()
{
	Entity* debug = new Entity;
	debugText = new Text(Vector2(0.0f, 0.0f), "Debug info: Loading...");
	debug->addComponent(debugText);
	debugText->setEntity(debug);
	GazEngine::addEntity(debug);
}
