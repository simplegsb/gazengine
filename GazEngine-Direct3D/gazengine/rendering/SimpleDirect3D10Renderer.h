#ifndef SIMPLEDIRECT3D10RENDERER_H_
#define SIMPLEDIRECT3D10RENDERER_H_

#include "Direct3D10Renderer.h"

class SimpleDirect3D10Renderer : public Direct3D10Renderer
{
	public:
		SimpleDirect3D10Renderer(ID3D10Device& device);

		~SimpleDirect3D10Renderer();

		void dispose();

		void init();

		void render(const Capsule& model);

		void render(const Circle& model);

		void render(const Cube& model);

		void render(const Cylinder& model);

		void render(const Line2& model);

		void render(const Mesh& model);

		void render(const Sphere& model);

		void render(const Text& model);

		void render(const Torus& model);

	private:
		ID3D10Device& device;

		ID3DX10Font* font;
};

#endif /* SIMPLEDIRECT3D10RENDERER_H_ */
