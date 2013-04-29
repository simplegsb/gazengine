#ifndef GDIRENDERINGENGINE_H_
#define GDIRENDERINGENGINE_H_

#include <vector>

#include <windows.h>

#include "../../graph/QuadTree.h"
#include "../../rendering/RenderingEngine.h"

class GDIRenderingEngine : public RenderingEngine
{
	public:
		GDIRenderingEngine(HWND window);

		virtual ~GDIRenderingEngine();

		void addModel(Model* model);

		void advance();

		void destroy();

		HDC getBuffer() const;

		int getHeight() const;

		QuadTree* getQuadTree() const;

		int getWidth() const;

		void init();

		void removeModel(const Model& model);

		void setHeight(int height);

		void setQuadTree(QuadTree* quadTree);

		void setWidth(int width);

	private:
		HBITMAP backBitmap;

		HBITMAP backBitmapOld;

		HDC backBuffer;

		HDC frontBuffer;

		int height;

		std::vector<Model*> models;

		QuadTree* quadTree;

		int width;

		HWND window;

		void drawQuadTree(const QuadTree& quadTree) const;
};

#endif /* GDIRENDERINGENGINE_H_ */
