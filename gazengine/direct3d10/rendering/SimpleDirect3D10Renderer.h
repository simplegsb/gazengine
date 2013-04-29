#ifndef SIMPLEDIRECT3D10RENDERER_H_
#define SIMPLEDIRECT3D10RENDERER_H_

#include "Direct3D10Renderer.h"

class SimpleDirect3D10Renderer : public Direct3D10Renderer
{
	public:
		void dispose();

		void init();

		void render(const Circle& model);

		void render(const Mesh& model);

		void render(const Text& model);
};

#endif /* SIMPLEDIRECT3D10RENDERER_H_ */
