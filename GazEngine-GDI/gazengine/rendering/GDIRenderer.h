#ifndef GDIRENDERER_H_
#define GDIRENDERER_H_

#include <windows.h>

#include <gazengine/rendering/Renderer.h>

class GDIRenderer : public Renderer
{
	public:
		GDIRenderer();

		void dispose();

		void init();

		void render(const Capsule& model);

		void render(const Circle& model);

		void render(const Cylinder& model);

		void render(const Line2& model);

		void render(const Mesh& model);

		void render(const Sphere& model);

		void render(const Text& model);

		void render(const Torus& model);

		void setBuffer(HDC buffer);

	private:
		HDC buffer;
};

#endif /* GDIRENDERER_H_ */
