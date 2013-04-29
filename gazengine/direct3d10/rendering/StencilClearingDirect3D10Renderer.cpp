#include "StencilClearingDirect3D10Renderer.h"

#include "../model/Direct3D10Mesh.h"

StencilClearingDirect3D10Renderer::StencilClearingDirect3D10Renderer(ID3D10Device& device,
	ID3D10DepthStencilView& depthStencilView, Renderer* renderer) :
	depthStencilView(depthStencilView),
	device(device),
	renderer(renderer)
{
}

StencilClearingDirect3D10Renderer::~StencilClearingDirect3D10Renderer()
{
	if (renderer != NULL)
	{
		delete renderer;
	}
}

void StencilClearingDirect3D10Renderer::dispose()
{
	renderer->dispose();
}

void StencilClearingDirect3D10Renderer::init()
{
	renderer->init();

	device.ClearDepthStencilView(&depthStencilView, D3D10_CLEAR_STENCIL, 1.0f, 0);
}

void StencilClearingDirect3D10Renderer::render(const Circle& model)
{
	renderer->render(model);
}

void StencilClearingDirect3D10Renderer::render(const Mesh& model)
{
	renderer->render(model);
}

void StencilClearingDirect3D10Renderer::render(const Text& model)
{
	renderer->render(model);
}
