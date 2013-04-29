#ifndef GDIRENDERINGENGINE_H_
#define GDIRENDERINGENGINE_H_

#include <map>
#include <vector>

#include <windows.h>

#include "../../graph/QuadTree.h"
#include "../../rendering/RenderingEngine.h"

class GDIRenderingEngine : public RenderingEngine
{
	public:
		GDIRenderingEngine(HWND window);

		virtual ~GDIRenderingEngine();

		void addEntity(Entity* entity);

		void addModel(Model* model);

		void addRenderer(Renderer* renderer);

		void advance();

		void destroy();

		HDC getBuffer() const;

		int getHeight() const;

		QuadTree* getQuadTree() const;

		int getWidth() const;

		void init();

		void removeEntity(const Entity& entity);

		void removeModel(const Model& model);

		void removeRenderer(const Renderer& renderer);

		void setHeight(int height);

		void setQuadTree(QuadTree* quadTree);

		void setRendererRoot(const Renderer& renderer, const Tree& node);

		void setWidth(int width);

	private:
		HBITMAP backBitmap;

		HBITMAP backBitmapOld;

		HDC backBuffer;

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
