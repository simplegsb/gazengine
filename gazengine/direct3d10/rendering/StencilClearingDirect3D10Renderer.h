#ifndef STENCILCLEARINGDIRECT3D10RENDERER_H_
#define STENCILCLEARINGDIRECT3D10RENDERER_H_

#include "Direct3D10Renderer.h"

class StencilClearingDirect3D10Renderer : public Direct3D10Renderer
{
	public:
		StencilClearingDirect3D10Renderer(ID3D10Device& device, ID3D10DepthStencilView& depthStencilView,
			Renderer* renderer);

		~StencilClearingDirect3D10Renderer();

		void dispose();

		void init();

		void render(const Circle& model);

		void render(const Mesh& model);

		void render(const Text& model);

	private:
		ID3D10DepthStencilView& depthStencilView;

		ID3D10Device& device;

		Renderer* renderer;

		StencilClearingDirect3D10Renderer(const StencilClearingDirect3D10Renderer& original);

		StencilClearingDirect3D10Renderer& operator=(const StencilClearingDirect3D10Renderer& original);
};

#endif /* STENCILCLEARINGDIRECT3D10RENDERER_H_ */
