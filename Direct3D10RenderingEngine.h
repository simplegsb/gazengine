#ifndef DIRECT3D10RENDERINGENGINE_H_
#define DIRECT3D10RENDERINGENGINE_H_

#include <vector>

#include <d3d10.h>
#pragma comment (lib, "d3d10.lib")

#include "Direct3D10Camera.h"
#include "Direct3D10Light.h"
#include "Direct3D10Shader.h"
#include "Engine.h"
#include "Model.h"

class Direct3D10RenderingEngine : public Engine
{
	public:
		Direct3D10RenderingEngine(HWND window);

		virtual ~Direct3D10RenderingEngine();

		void addLight(Direct3D10Light* light);

		void addModel(Model* model);

		void advance();

		void destroy();

		Direct3D10Camera* getCamera() const;

		const D3DXCOLOR& getClearingColour() const;

		ID3D10Device* getDevice() const;

		int getHeight() const;

		Direct3D10Shader* getShader() const;

		int getWidth() const;

		void init();

		void setCamera(Direct3D10Camera* camera);

		void setClearingColour(const D3DXCOLOR& clearingColour);

		void setHeight(int height);

		void setShader(Direct3D10Shader* shader);

		void setWidth(int width);

	private:
		Direct3D10Camera* camera;

		D3DXCOLOR clearingColour;

		ID3D10Device* device;

		int height;

		std::vector<Direct3D10Light*> lights;

		std::vector<Model*> models;

		ID3D10RenderTargetView* renderTargetView;

		Direct3D10Shader* shader;

		IDXGISwapChain* swapChain;

		int width;

		HWND window;

		void createRenderTargetView();

		DXGI_SWAP_CHAIN_DESC createSwapChainDescription();

		void initViewport();
};

#endif /* DIRECT3D10RENDERINGENGINE_H_ */
