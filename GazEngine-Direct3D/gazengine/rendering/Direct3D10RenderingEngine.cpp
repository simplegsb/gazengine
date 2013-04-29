#include <algorithm>

#include <d3dx10.h>
#pragma comment (lib, "d3dx10.lib")

#include "Direct3D10RenderingEngine.h"
#include "Direct3D10Texture.h"

using namespace std;

Direct3D10RenderingEngine::Direct3D10RenderingEngine(HWND window) :
	camera(NULL),
	clearingColour(0.0f, 0.0f, 0.0f, 1.0f),
	depthStencilBuffer(NULL),
	depthStencilView(NULL),
	device(NULL),
	height(600),
	models(),
	renderTargetView(NULL),
	swapChain(NULL),
	tree(NULL),
	width(800),
	window(window)
{
	UINT flags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
    flags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

	DXGI_SWAP_CHAIN_DESC swapChainDescription = createSwapChainDescription();
    D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, flags, D3D10_SDK_VERSION, &swapChainDescription,
		&swapChain, &device);
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

	for (unsigned int index = 0; index < renderers.size(); index++)
	{
		delete renderers.at(index);
	}
}

void Direct3D10RenderingEngine::addEntity(Entity* entity)
{
	vector<Model*> entityModels = entity->getComponents<Model>();
	for (unsigned int index = 0; index < entityModels.size(); index++)
	{
		models.push_back(entityModels[index]);
	}
}

void Direct3D10RenderingEngine::addLight(Light* light)
{
	lights.push_back(static_cast<Direct3D10Light*>(light));
}

void Direct3D10RenderingEngine::addModel(Model* model)
{
	models.push_back(model);
}

void Direct3D10RenderingEngine::addRenderer(Renderer* renderer)
{
	renderers.push_back(renderer);

	if (tree != NULL)
	{
		rendererRoots[renderer] = tree;
	}
}

void Direct3D10RenderingEngine::advance()
{
	device->ClearRenderTargetView(renderTargetView, clearingColour.getData());
    device->ClearDepthStencilView(depthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);

	if (tree != NULL)
	{
		for (unsigned int index = 0; index < renderers.size(); index++)
		{
			Direct3D10Renderer& renderer = static_cast<Direct3D10Renderer&>(*renderers[index]);
			renderer.init();

			renderer.getShader()->setVar("cameraTransformation", camera->getFinalTransformation());
			renderer.getShader()->setVar("cameraTranslation", camera->getTranslation());

			for (unsigned int index = 0; index < lights.size(); index++)
			{
				lights.at(index)->apply(*renderer.getShader());
			}

			const SimpleTree& simpleTree = *rendererRoots[&renderer];

			Matrix44 origin;
			origin.setIdentity();
			if (simpleTree.getParent() != NULL)
			{
				origin = simpleTree.getParent()->getAbsoluteTransformation();
			}

			renderTree(renderer, simpleTree, origin);

			renderer.dispose();
		}
	}

    swapChain->Present(NULL, NULL);
}

void Direct3D10RenderingEngine::createDepthStencilView()
{
	D3D10_TEXTURE2D_DESC depthStencilDescription;
	depthStencilDescription.ArraySize = 1;
	depthStencilDescription.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	depthStencilDescription.CPUAccessFlags = 0; 
	depthStencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDescription.Height = height;
	depthStencilDescription.MipLevels = 1;
	depthStencilDescription.MiscFlags = 0;
	depthStencilDescription.SampleDesc.Count = 1;
	depthStencilDescription.SampleDesc.Quality = 0;
	depthStencilDescription.Usage = D3D10_USAGE_DEFAULT;
	depthStencilDescription.Width = width;

	device->CreateTexture2D(&depthStencilDescription, NULL, &depthStencilBuffer);
	device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
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
	if (depthStencilBuffer != NULL)
	{
		depthStencilBuffer->Release();
	}

	if (depthStencilView != NULL)
	{
		depthStencilView->Release();
	}

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

Camera* Direct3D10RenderingEngine::getCamera() const
{
	return camera;
}

const Vector4& Direct3D10RenderingEngine::getClearingColour() const
{
	return clearingColour;
}

ID3D10DepthStencilView* Direct3D10RenderingEngine::getDepthStencilView() const
{
	return depthStencilView;
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
	createDepthStencilView();
    createRenderTargetView();
    device->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
	
	initViewport();
}

void Direct3D10RenderingEngine::initViewport()
{
	D3D10_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D10_VIEWPORT));

    viewport.Height = height;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f;
    viewport.Width = width;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;

    device->RSSetViewports(1, &viewport);
}

void Direct3D10RenderingEngine::removeEntity(const Entity& entity)
{
	vector<Model*> entityModels = entity.getComponents<Model>();
	for (unsigned int index = 0; index < entityModels.size(); index++)
	{
		models.erase(remove(models.begin(), models.end(), entityModels[index]));
	}
}

void Direct3D10RenderingEngine::removeModel(const Model& model)
{
	models.erase(remove(models.begin(), models.end(), &model));
	delete &model;
}

void Direct3D10RenderingEngine::removeRenderer(const Renderer& renderer)
{
	renderers.erase(remove(renderers.begin(), renderers.end(), &renderer));
	rendererRoots.erase(&renderer);
	delete &renderer;
}

void Direct3D10RenderingEngine::renderModel(Direct3D10Renderer& renderer, const Model& model, const Matrix44& transformation)
{
	renderer.getShader()->setVar("worldTransformation", transformation);

	if (model.getNormalMap() != NULL)
	{
		static_cast<Direct3D10Texture*>(model.getNormalMap())->apply(*renderer.getShader());
	}
	if (model.getTexture() != NULL)
	{
		static_cast<Direct3D10Texture*>(model.getTexture())->apply(*renderer.getShader());
	}

	renderer.getShader()->setVar("material", "ambient", model.getMaterial().ambient);
	renderer.getShader()->setVar("material", "diffuse", model.getMaterial().diffuse);
	renderer.getShader()->setVar("material", "emmissive", model.getMaterial().emmissive);
	renderer.getShader()->setVar("material", "specular", model.getMaterial().specular);
	renderer.getShader()->setVar("material", "specularPower", model.getMaterial().specularPower);

	renderer.getShader()->apply();

	model.render(renderer);
}

void Direct3D10RenderingEngine::renderTree(Direct3D10Renderer& renderer, const SimpleTree& root,
	const Matrix44& parentTransformation)
{
	Matrix44 worldTransformation = parentTransformation * root.getTransformation();

	if (root.getModel() != NULL)
	{
		renderModel(renderer, *root.getModel(), worldTransformation);
	}

	for (unsigned int index = 0; index < root.getChildren().size(); index++)
	{
		renderTree(renderer, *root.getChildren()[index], worldTransformation);
	}
}

void Direct3D10RenderingEngine::setCamera(Camera* camera)
{
	this->camera = camera;
}

void Direct3D10RenderingEngine::setClearingColour(const Vector4& clearingColour)
{
	this->clearingColour = clearingColour;
}

void Direct3D10RenderingEngine::setHeight(int height)
{
	this->height = height;
}

void Direct3D10RenderingEngine::setRendererRoot(const Renderer& renderer, const SimpleTree& node)
{
	rendererRoots[&renderer] = &node;
}

void Direct3D10RenderingEngine::setTree(const SimpleTree* tree)
{
	this->tree = tree;

	for (unsigned int index = 0; index < renderers.size(); index++)
	{
		rendererRoots[renderers[index]] = tree;
	}
}

void Direct3D10RenderingEngine::setWidth(int width)
{
	this->width = width;
}
