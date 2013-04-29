#ifndef DIRECT3D10RENDERINGENGINE_H_
#define DIRECT3D10RENDERINGENGINE_H_

#include <map>
#include <vector>

#include <d3d10.h>
#pragma comment (lib, "d3d10.lib")

#include "../../graph/SimpleTree.h"
#include "../../rendering/Renderer.h"
#include "../../rendering/RenderingEngine.h"
#include "../scene/Direct3D10Camera.h"
#include "../scene/Direct3D10Light.h"
#include "Direct3D10Renderer.h"

class Direct3D10RenderingEngine : public RenderingEngine
{
	public:
		Direct3D10RenderingEngine(HWND window);

		virtual ~Direct3D10RenderingEngine();

		void addLight(Direct3D10Light* light);

		void addModel(Model* model);

		void addRenderer(Renderer* renderer);

		void advance();

		void destroy();

		Direct3D10Camera* getCamera() const;

		const D3DXCOLOR& getClearingColour() const;

		ID3D10DepthStencilView* getDepthStencilView() const;

		ID3D10Device* getDevice() const;

		int getHeight() const;

		const SimpleTree* getTree() const;

		int getWidth() const;

		void init();

		void removeModel(const Model& model);

		void removeRenderer(const Renderer& renderer);

		void setCamera(Direct3D10Camera* camera);

		void setClearingColour(const D3DXCOLOR& clearingColour);

		void setHeight(int height);

		void setRendererRoot(const Renderer& renderer, const Tree& node);

		void setTree(SimpleTree* tree);

		void setWidth(int width);

	private:
		Direct3D10Camera* camera;

		D3DXCOLOR clearingColour;

		ID3D10Texture2D* depthStencilBuffer;

		ID3D10DepthStencilView* depthStencilView;

		ID3D10Device* device;

		int height;

		std::vector<Direct3D10Light*> lights;

		std::vector<Model*> models;

		std::map<const Renderer*, const Tree*> rendererRoots;

		std::vector<Renderer*> renderers;

		ID3D10RenderTargetView* renderTargetView;

		IDXGISwapChain* swapChain;

		SimpleTree* tree;

		int width;

		HWND window;

		void createDepthStencilView();

		void createRenderTargetView();

		DXGI_SWAP_CHAIN_DESC createSwapChainDescription();

		void initViewport();

		void renderModel(Direct3D10Renderer& renderer, const Model& model, const D3DXMATRIX& transformation);

		void renderTree(Direct3D10Renderer& renderer, const SimpleTree& tree, const D3DXMATRIX& parentTransformation);
};

#endif /* DIRECT3D10RENDERINGENGINE_H_ */
