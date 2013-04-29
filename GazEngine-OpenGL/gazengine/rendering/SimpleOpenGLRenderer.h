#ifndef SIMPLEOPENGLRENDERER_H_
#define SIMPLEOPENGLRENDERER_H_

#include <gazengine/rendering/Renderer.h>

class SimpleOpenGLRenderer : public Renderer
{
	public:
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
		int getOpenGLDrawingMode(Model::PrimitiveType primitiveType);
};

#endif /* SIMPLEOPENGLRENDERER_H_ */
