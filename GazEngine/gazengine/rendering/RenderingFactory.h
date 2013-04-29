#ifndef RENDERINGFACTORY_H_
#define RENDERINGFACTORY_H_

#include <string>

#include "Texture.h"

class RenderingFactory
{
	public:
		virtual ~RenderingFactory()
		{
		}

		virtual Texture* createTexture(const std::string& fileName) = 0;

		static RenderingFactory* getInstance();

		static void setInstance(RenderingFactory* instance);

	private:
		static RenderingFactory* instance;
};

#endif /* RENDERINGFACTORY_H_ */
