#ifndef OPENGLRENDERINGENGINE_H_
#define OPENGLRENDERINGENGINE_H_

#include <map>

#include <gazengine/rendering/RenderingEngine.h>

class OpenGLRenderingEngine : public RenderingEngine
{
	public:
		OpenGLRenderingEngine();

		~OpenGLRenderingEngine();

		void addEntity(Entity* entity);

		void addLight(Light* light);

		void addModel(Model* model);

		void addRenderer(Renderer* renderer);

		void advance();

		void destroy();

		Camera* getCamera() const;

		const Vector4& getClearingColour() const;

		const SimpleTree* getTree() const;

		int getHeight() const;

		int getWidth() const;

		void init();

		void removeEntity(const Entity& entity);

		void removeModel(const Model& model);

		void removeRenderer(const Renderer& renderer);

		void setCamera(Camera* camera);

		void setClearingColour(const Vector4& clearingColour);

		void setHeight(int height);

		void setRendererRoot(const Renderer& renderer, const SimpleTree& node);

		void setTree(SimpleTree* tree);

		void setWidth(int width);

	private:
		Camera* camera;

		Vector4 clearingColour;

		int height;

		std::vector<Light*> lights;

		std::map<const Renderer*, const SimpleTree*> rendererRoots;

		std::vector<Renderer*> renderers;

		SimpleTree* tree;

		int width;

		void renderTree(Renderer& renderer, const SimpleTree& root);
};

#endif /* OPENGLRENDERINGENGINE_H_ */
