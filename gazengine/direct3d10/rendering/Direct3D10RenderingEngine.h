#ifndef DIRECT3D10RENDERINGENGINE_H_
#define DIRECT3D10RENDERINGENGINE_H_

#include <vector>

#include <d3d10.h>
#pragma comment (lib, "d3d10.lib")

#include "../../graph/SimpleTree.h"
#include "../../rendering/RenderingEngine.h"
#include "../scene/Direct3D10Camera.h"
#include "../scene/Direct3D10Light.h"

class Direct3D10RenderingEngine : public RenderingEngine
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

		const SimpleTree* getTree() const;

		int getWidth() const;

		void init();

		void removeModel(const Model& model);

		void setCamera(Direct3D10Camera* camera);

		void setClearingColour(const D3DXCOLOR& clearingColour);

		void setHeight(int height);

		void setTree(SimpleTree* tree);

		void setWidth(int width);

	private:
		Direct3D10Camera* camera;

		D3DXCOLOR clearingColour;

		ID3D10Device* device;

		int height;

		std::vector<Direct3D10Light*> lights;

		std::vector<Model*> models;

		ID3D10RenderTargetView* renderTargetView;

		IDXGISwapChain* swapChain;

		SimpleTree* tree;

		int width;

		HWND window;

		void createRenderTargetView();

		DXGI_SWAP_CHAIN_DESC createSwapChainDescription();

		void initViewport();

		void renderModel(Model& model, const D3DXMATRIX& transformation);

		void renderTree(SimpleTree& tree, const D3DXMATRIX& parentTransformation);
};

#endif /* DIRECT3D10RENDERINGENGINE_H_ */
