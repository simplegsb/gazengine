#include "RenderingFactory.h"

RenderingFactory* RenderingFactory::instance = NULL;

RenderingFactory* RenderingFactory::getInstance()
{
	return instance;
}

void RenderingFactory::setInstance(RenderingFactory* instance)
{
	RenderingFactory::instance = instance;
}
