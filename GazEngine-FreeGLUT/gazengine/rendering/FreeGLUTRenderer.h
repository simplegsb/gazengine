#ifndef FREEGLUTRENDERER_H_
#define FREEGLUTRENDERER_H_

#include <gazengine/rendering/Renderer.h>

class FreeGLUTRenderer : public Renderer
{
	public:
		FreeGLUTRenderer(Renderer* renderer);

		~FreeGLUTRenderer();

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

	private:
		Renderer* renderer;
};

#endif /* FREEGLUTRENDERER_H_ */
