#ifndef GDIRENDERER_H_
#define GDIRENDERER_H_

#include <windows.h>

#include "../../rendering/Renderer.h"

class GDIRenderer : public Renderer
{
	public:
		GDIRenderer(HDC buffer);

		void dispose();

		void init();

		void render(const Circle& model);

		void render(const Mesh& model);

	private:
		HDC buffer;
};

#endif /* GDIRENDERER_H_ */
