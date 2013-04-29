#ifndef DIRECT3D10RENDERINGFACTORY_H_
#define DIRECT3D10RENDERINGFACTORY_H_

#include <d3d10.h>

#include <gazengine/rendering/RenderingFactory.h>

class Direct3D10RenderingFactory : public RenderingFactory
{
	public:
		Direct3D10RenderingFactory(ID3D10Device& device);

		Texture* createTexture(const std::string& fileName);

	private:
		ID3D10Device& device;
};

#endif /* DIRECT3D10RENDERINGFACTORY_H_ */
