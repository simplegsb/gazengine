#ifndef RENDERER_H_
#define RENDERER_H_

class Circle;
class Mesh;
class Model;
class Text;

class Renderer
{
	public:
		virtual void dispose() = 0;

		virtual void init() = 0;

		virtual void render(const Circle& model) = 0;

		virtual void render(const Mesh& model) = 0;

		virtual void render(const Text& model) = 0;
};

#endif /* RENDERER_H_ */
