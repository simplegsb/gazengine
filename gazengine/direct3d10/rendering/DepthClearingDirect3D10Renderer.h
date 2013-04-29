#ifndef DEPTHCLEARINGDIRECT3D10RENDERER_H_
#define DEPTHCLEARINGDIRECT3D10RENDERER_H_

#include "Direct3D10Renderer.h"

class DepthClearingDirect3D10Renderer : public Direct3D10Renderer
{
	public:
		DepthClearingDirect3D10Renderer(ID3D10Device& device, ID3D10DepthStencilView& depthStencilView,
			Renderer* renderer);

		~DepthClearingDirect3D10Renderer();

		void dispose();

		void init();

		void render(const Circle& model);

		void render(const Mesh& model);

	private:
		ID3D10DepthStencilView& depthStencilView;

		ID3D10Device& device;

		Renderer* renderer;

		DepthClearingDirect3D10Renderer(const DepthClearingDirect3D10Renderer& original);

		DepthClearingDirect3D10Renderer& operator=(const DepthClearingDirect3D10Renderer& original);
};

#endif /* DEPTHCLEARINGDIRECT3D10RENDERER_H_ */
