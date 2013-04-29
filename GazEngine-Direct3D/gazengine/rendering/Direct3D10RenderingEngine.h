#ifndef DIRECT3D10RENDERINGENGINE_H_
#define DIRECT3D10RENDERINGENGINE_H_

#include <map>

#include <d3d10.h>
#pragma comment (lib, "d3d10.lib")

#include <gazengine/rendering/RenderingEngine.h>

#include "../scene/Direct3D10Light.h"
#include "Direct3D10Renderer.h"

class Direct3D10RenderingEngine : public RenderingEngine
{
	public:
		Direct3D10RenderingEngine(HWND window);

		~Direct3D10RenderingEngine();

		void addEntity(Entity* entity);

		void addLight(Light* light);

		void addModel(Model* model);

		void addRenderer(Renderer* renderer);

		void advance();

		void destroy();

		Camera* getCamera() const;

		const Vector4& getClearingColour() const;

		ID3D10DepthStencilView* getDepthStencilView() const;

		ID3D10Device* getDevice() const;

		int getHeight() const;

		const SimpleTree* getTree() const;

		int getWidth() const;

		void init();

		void removeEntity(const Entity& entity);

		void removeModel(const Model& model);

		void removeRenderer(const Renderer& renderer);

		void setCamera(Camera* camera);

		void setClearingColour(const Vector4& clearingColour);

		void setHeight(int height);

		void setRendererRoot(const Renderer& renderer, const SimpleTree& node);

		void setTree(const SimpleTree* tree);

		void setWidth(int width);

	private:
		Camera* camera;

		Vector4 clearingColour;

		ID3D10Texture2D* depthStencilBuffer;

		ID3D10DepthStencilView* depthStencilView;

		ID3D10Device* device;

		int height;

		std::vector<Direct3D10Light*> lights;

		std::vector<Model*> models;

		std::map<const Renderer*, const SimpleTree*> rendererRoots;

		std::vector<Renderer*> renderers;

		ID3D10RenderTargetView* renderTargetView;

		IDXGISwapChain* swapChain;

		const SimpleTree* tree;

		int width;

		HWND window;

		void createDepthStencilView();

		void createRenderTargetView();

		DXGI_SWAP_CHAIN_DESC createSwapChainDescription();

		void initViewport();

		void renderModel(Direct3D10Renderer& renderer, const Model& model, const Matrix44& transformation);

		void renderTree(Direct3D10Renderer& renderer, const SimpleTree& root, const Matrix44& parentTransformation);
};

#endif /* DIRECT3D10RENDERINGENGINE_H_ */
