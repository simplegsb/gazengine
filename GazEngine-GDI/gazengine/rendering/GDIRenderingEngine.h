#ifndef GDIRENDERINGENGINE_H_
#define GDIRENDERINGENGINE_H_

#include <map>
#include <vector>

#include <windows.h>

#include <gazengine/graph/QuadTree.h>
#include <gazengine/rendering/RenderingEngine.h>

class GDIRenderingEngine : public RenderingEngine
{
	public:
		GDIRenderingEngine(HWND window);

		virtual ~GDIRenderingEngine();

		void addEntity(Entity* entity);

		void addLight(Light* light);

		void addModel(Model* model);

		void addRenderer(Renderer* renderer);

		void advance();

		void destroy();

		HDC getBuffer() const;

		const Camera* getCamera() const;

		const Vector4& getClearingColour() const;

		int getHeight() const;

		QuadTree* getQuadTree() const;

		int getWidth() const;

		void init();

		void removeEntity(const Entity& entity);

		void removeModel(const Model& model);

		void removeRenderer(const Renderer& renderer);

		void setCamera(Camera* camera);

		void setClearingColour(const Vector4& clearingColour);

		void setHeight(int height);

		void setQuadTree(QuadTree* quadTree);

		void setRendererRoot(const Renderer& renderer, const SimpleTree& node);

		void setWidth(int width);

	private:
		HBITMAP backBitmap;

		HBITMAP backBitmapOld;

		HDC backBuffer;

		Vector4 clearingColour;

		HDC frontBuffer;

		int height;

		std::vector<Model*> models;

		QuadTree* quadTree;

		std::map<const Renderer*, const Tree*> rendererRoots;

		std::vector<Renderer*> renderers;

		int width;

		HWND window;

		void renderQuadTree(Renderer& renderer, const QuadTree& quadTree) const;
};

#endif /* GDIRENDERINGENGINE_H_ */
