#ifndef RENDERER_H_
#define RENDERER_H_

class Capsule;
class Circle;
class Cylinder;
class Line2;
class Mesh;
class Model;
class Sphere;
class Text;
class Torus;

class Renderer
{
	public:
		virtual void dispose() = 0;

		virtual void init() = 0;

		virtual void render(const Capsule& model) = 0;

		virtual void render(const Circle& model) = 0;

		virtual void render(const Cylinder& model) = 0;

		virtual void render(const Line2& model) = 0;

		virtual void render(const Mesh& model) = 0;

		virtual void render(const Sphere& model) = 0;

		virtual void render(const Text& model) = 0;

		virtual void render(const Torus& model) = 0;
};

#endif /* RENDERER_H_ */
