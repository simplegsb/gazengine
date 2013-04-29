#include "SimpleDirect3D10Renderer.h"

#include "../model/Direct3D10Mesh.h"

void SimpleDirect3D10Renderer::dispose()
{
}

void SimpleDirect3D10Renderer::init()
{
}

void SimpleDirect3D10Renderer::render(const Circle&)
{
}

void SimpleDirect3D10Renderer::render(const Mesh& model)
{
	static_cast<const Direct3D10Mesh&>(model).getMesh()->DrawSubset(0);
}
