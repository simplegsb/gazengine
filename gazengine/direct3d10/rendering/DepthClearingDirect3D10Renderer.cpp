#include "DepthClearingDirect3D10Renderer.h"

#include "../model/Direct3D10Mesh.h"

DepthClearingDirect3D10Renderer::DepthClearingDirect3D10Renderer(ID3D10Device& device,
	ID3D10DepthStencilView& depthStencilView, Renderer* renderer) :
	depthStencilView(depthStencilView),
	device(device),
	renderer(renderer)
{
}

DepthClearingDirect3D10Renderer::~DepthClearingDirect3D10Renderer()
{
	if (renderer != NULL)
	{
		delete renderer;
	}
}

void DepthClearingDirect3D10Renderer::dispose()
{
	renderer->dispose();
}

void DepthClearingDirect3D10Renderer::init()
{
	renderer->init();

	device.ClearDepthStencilView(&depthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
}

void DepthClearingDirect3D10Renderer::render(const Circle& model)
{
	renderer->render(model);
}

void DepthClearingDirect3D10Renderer::render(const Mesh& model)
{
	renderer->render(model);
}
