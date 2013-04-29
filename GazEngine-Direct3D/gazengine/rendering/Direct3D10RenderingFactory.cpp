#include "Direct3D10RenderingFactory.h"
#include "Direct3D10Texture.h"

using namespace std;

Direct3D10RenderingFactory::Direct3D10RenderingFactory(ID3D10Device& device) :
	device(device)
{
}

Texture* Direct3D10RenderingFactory::createTexture(const string& fileName)
{
	return new Direct3D10Texture(device, wstring(fileName.begin(), fileName.end()));
}
