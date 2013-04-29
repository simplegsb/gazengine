#include "../model/GDICircle.h"
#include "../model/GDIMesh.h"
#include "GDIRenderer.h"

using namespace std;

GDIRenderer::GDIRenderer(HDC buffer) :
	buffer(buffer)
{
}

void GDIRenderer::render(const Circle& model)
{
	const GDICircle& gdiCircle = static_cast<const GDICircle&>(model);

	HPEN pen = CreatePen(PS_SOLID, 1, gdiCircle.getColour());
	SelectObject(buffer, pen);

	Ellipse(buffer,
		static_cast<int>(gdiCircle.getPosition().x - gdiCircle.getRadius()),
		static_cast<int>(gdiCircle.getPosition().y - gdiCircle.getRadius()),
		static_cast<int>(gdiCircle.getPosition().x + gdiCircle.getRadius()),
		static_cast<int>(gdiCircle.getPosition().y + gdiCircle.getRadius()));

	DeleteObject(pen);
}

void GDIRenderer::render(const Mesh& model)
{
	const GDIMesh& gdiMesh = static_cast<const GDIMesh&>(model);

	if (gdiMesh.getVertices().empty())
	{
		return;
	}

	HPEN pen = CreatePen(PS_SOLID, 1, gdiMesh.getColour());
	SelectObject(buffer, pen);

	MoveToEx(buffer, (int) gdiMesh.getVertices().at(0).x, (int) gdiMesh.getVertices().at(0).y, NULL);

	for (unsigned int index = 1; index < gdiMesh.getVertices().size(); index++)
	{
		LineTo(buffer, (int) gdiMesh.getVertices().at(index).x, (int) gdiMesh.getVertices().at(index).y);
	}

	DeleteObject(pen);
}
