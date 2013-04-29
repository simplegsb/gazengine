#include "stdafx.h"

#include <algorithm>

#include <d3dx10.h>
#pragma comment (lib, "d3dx10.lib")

#include "../model/Direct3D10Mesh.h"
#include "Direct3D10RenderingEngine.h"

Direct3D10RenderingEngine::Direct3D10RenderingEngine(HWND window) :
	camera(NULL),
	clearingColour(0.0f, 0.2f, 0.4f, 1.0f),
	device(NULL),
	height(600),
	models(),
	renderTargetView(NULL),
	swapChain(NULL),
	tree(NULL),
	width(800),
	window(window)
{
}

Direct3D10RenderingEngine::~Direct3D10RenderingEngine()
{
	if (camera != NULL)
	{
		delete camera;
	}

	for (unsigned int index = 0; index < lights.size(); index++)
	{
		delete lights.at(index);
	}

	for (unsigned int index = 0; index < models.size(); index++)
	{
		delete models.at(index);
	}

	if (tree != NULL)
	{
		delete tree;
	}
}

void Direct3D10RenderingEngine::addLight(Direct3D10Light* light)
{
	lights.push_back(light);
}

void Direct3D10RenderingEngine::addModel(Model* model)
{
	models.push_back(model);
}

void Direct3D10RenderingEngine::advance()
{
    device->ClearRenderTargetView(renderTargetView, clearingColour);

	if (tree != NULL)
	{
		D3DXMATRIX origin;
		D3DXMatrixIdentity(&origin);
		renderTree(*tree, origin);
	}

    swapChain->Present(0, 0);
}

void Direct3D10RenderingEngine::createRenderTargetView()
{
	ID3D10Texture2D* backBuffer;

    swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &backBuffer);
    device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);

    backBuffer->Release();
}

DXGI_SWAP_CHAIN_DESC Direct3D10RenderingEngine::createSwapChainDescription()
{
	DXGI_SWAP_CHAIN_DESC swapChainDescription;
    ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

    swapChainDescription.BufferCount = 1;
    swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDescription.BufferDesc.Height = height;
    swapChainDescription.BufferDesc.Width = width;
    swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swapChainDescription.OutputWindow = window;
    swapChainDescription.SampleDesc.Count = 1;
    swapChainDescription.SampleDesc.Quality = 0;
    swapChainDescription.Windowed = true;

	return swapChainDescription;
}

void Direct3D10RenderingEngine::destroy()
{
	if (device != NULL)
	{
		device->ClearState();
		device->Release();
	}

	if (renderTargetView != NULL)
	{
		renderTargetView->Release();
	}

	if (swapChain != NULL)
	{
		swapChain->Release();
	}
}

Direct3D10Camera* Direct3D10RenderingEngine::getCamera() const
{
	return camera;
}

const D3DXCOLOR& Direct3D10RenderingEngine::getClearingColour() const
{
	return clearingColour;
}

ID3D10Device* Direct3D10RenderingEngine::getDevice() const
{
	return device;
}

int Direct3D10RenderingEngine::getHeight() const
{
	return height;
}

const SimpleTree* Direct3D10RenderingEngine::getTree() const
{
	return tree;
}

int Direct3D10RenderingEngine::getWidth() const
{
	return width;
}

void Direct3D10RenderingEngine::init()
{
	DXGI_SWAP_CHAIN_DESC swapChainDescription = createSwapChainDescription();
    D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, &swapChainDescription,
		&swapChain, &device);

    createRenderTargetView();
    device->OMSetRenderTargets(1, &renderTargetView, NULL);
	
    initViewport();
}

void Direct3D10RenderingEngine::initViewport()
{
	D3D10_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D10_VIEWPORT));

    viewport.Height = height;
    viewport.Width = width;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;

    device->RSSetViewports(1, &viewport);
}

void Direct3D10RenderingEngine::removeModel(const Model& model)
{
	models.erase(remove(models.begin(), models.end(), &model));
	delete &model;
}

void Direct3D10RenderingEngine::renderModel(Model& model, const D3DXMATRIX& transformation)
{
	const Direct3D10Mesh* mesh = dynamic_cast<const Direct3D10Mesh*>(&model);
	if (mesh != NULL)
	{
		Direct3D10Shader* shader = mesh->getShader();

		shader->setVar("cameraTransformation", camera->getFinalTransformation());
		shader->setVar("cameraTranslation", camera->getTranslation());
		shader->setVar("worldTransformation", transformation);

		for (unsigned int index = 0; index < lights.size(); index++)
		{
			lights.at(index)->apply(*mesh->getShader());
		}

		shader->apply();
	}

	model.draw();
}

void Direct3D10RenderingEngine::renderTree(SimpleTree& tree, const D3DXMATRIX& parentTransformation)
{
	D3DXMATRIX worldTransformation = parentTransformation * tree.getTransformation();

	if (tree.getModel() != NULL)
	{
		renderModel(*tree.getModel(), worldTransformation);
	}

	for (unsigned int index = 0; index < tree.getChildren().size(); index++)
	{
		renderTree(*tree.getChildren().at(index), worldTransformation);
	}
}

void Direct3D10RenderingEngine::setCamera(Direct3D10Camera* camera)
{
	this->camera = camera;
}

void Direct3D10RenderingEngine::setClearingColour(const D3DXCOLOR& clearingColour)
{
	this->clearingColour = clearingColour;
}

void Direct3D10RenderingEngine::setHeight(int height)
{
	this->height = height;
}

void Direct3D10RenderingEngine::setTree(SimpleTree* tree)
{
	this->tree = tree;
}

void Direct3D10RenderingEngine::setWidth(int width)
{
	this->width = width;
}
