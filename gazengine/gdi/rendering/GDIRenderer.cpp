#include "../../model/Line2.h"
#include "../../model/Text.h"
#include "../model/GDICircle.h"
#include "../model/GDIMesh.h"
#include "GDIRenderer.h"

using namespace std;

GDIRenderer::GDIRenderer() :
	buffer(NULL)
{
}

void GDIRenderer::dispose()
{
}

void GDIRenderer::init()
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

void GDIRenderer::render(const Line2& model)
{
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(buffer, pen);

	MoveToEx(buffer, (int) model.getPointA().x, (int) model.getPointA().y, NULL);
	LineTo(buffer, (int) model.getPointB().x, (int) model.getPointB().y);

	DeleteObject(pen);	
}

void GDIRenderer::render(const Mesh& model)
{
	const GDIMesh& gdiMesh = static_cast<const GDIMesh&>(model);

	if (gdiMesh.getVertices().empty())
	{
		return;
	}

	if (model.getPrimitiveType() == Model::POINTS)
	{
		HBRUSH brush = CreateSolidBrush(gdiMesh.getColour());

		for (unsigned int index = 0; index < gdiMesh.getVertices().size(); index++)
		{
			RECT rectangle;
			rectangle.bottom = (int) gdiMesh.getVertices().at(index).y;
			rectangle.left = (int) gdiMesh.getVertices().at(index).x;
			rectangle.right = (int) gdiMesh.getVertices().at(index).x + 2;
			rectangle.top = (int) gdiMesh.getVertices().at(index).y + 2;

			FillRect(buffer, &rectangle, brush);
		}

		DeleteObject(brush);
	}
	else if (model.getPrimitiveType() == Model::LINE_LIST)
	{
		HPEN pen = CreatePen(PS_SOLID, 1, gdiMesh.getColour());
		SelectObject(buffer, pen);

		for (unsigned int index = 0; index < gdiMesh.getVertices().size(); index += 2)
		{
			MoveToEx(buffer, (int) gdiMesh.getVertices().at(index).x, (int) gdiMesh.getVertices().at(index).y, NULL);
			LineTo(buffer, (int) gdiMesh.getVertices().at(index + 1).x, (int) gdiMesh.getVertices().at(index + 1).y);
		}

		DeleteObject(pen);
	}
	else if (model.getPrimitiveType() == Model::LINE_STRIP)
	{
		HPEN pen = CreatePen(PS_SOLID, 1, gdiMesh.getColour());
		SelectObject(buffer, pen);

		MoveToEx(buffer, (int) gdiMesh.getVertices().at(0).x, (int) gdiMesh.getVertices().at(0).y, NULL);

		for (unsigned int index = 1; index < gdiMesh.getVertices().size(); index++)
		{
			LineTo(buffer, (int) gdiMesh.getVertices().at(index).x, (int) gdiMesh.getVertices().at(index).y);
		}

		DeleteObject(pen);
	}
	else if (model.getPrimitiveType() == Model::TRIANGLE_LIST)
	{
		HPEN pen = CreatePen(PS_SOLID, 1, gdiMesh.getColour());
		SelectObject(buffer, pen);

		MoveToEx(buffer, (int) gdiMesh.getVertices().at(0).x, (int) gdiMesh.getVertices().at(0).y, NULL);

		for (unsigned int index = 1; index < gdiMesh.getVertices().size(); index++)
		{
			LineTo(buffer, (int) gdiMesh.getVertices().at(index).x, (int) gdiMesh.getVertices().at(index).y);

			if ((index + 1) % 3 == 0)
			{
				LineTo(buffer, (int) gdiMesh.getVertices().at(index - 2).x, (int) gdiMesh.getVertices().at(index - 2).y);
			}
		}

		DeleteObject(pen);
	}
	else if (model.getPrimitiveType() == Model::TRIANGLE_STRIP)
	{
		HPEN pen = CreatePen(PS_SOLID, 1, gdiMesh.getColour());
		SelectObject(buffer, pen);

		for (unsigned int index = 2; index < gdiMesh.getVertices().size(); index++)
		{
			MoveToEx(buffer, (int) gdiMesh.getVertices().at(index - 2).x, (int) gdiMesh.getVertices().at(index - 2).y, NULL);
			LineTo(buffer, (int) gdiMesh.getVertices().at(index - 1).x, (int) gdiMesh.getVertices().at(index - 1).y);
			LineTo(buffer, (int) gdiMesh.getVertices().at(index).x, (int) gdiMesh.getVertices().at(index).y);
			LineTo(buffer, (int) gdiMesh.getVertices().at(index - 2).x, (int) gdiMesh.getVertices().at(index - 2).y);
		}

		DeleteObject(pen);
	}
}

void GDIRenderer::setBuffer(HDC buffer)
{
	this->buffer = buffer;
}

void GDIRenderer::render(const Text& model)
{
	RECT rectangle;
	rectangle.bottom = 10000; // Unlimited height
	rectangle.left = static_cast<LONG>(model.getPosition().x);
	rectangle.right = 10000; // Unlimited width
	rectangle.top = static_cast<LONG>(model.getPosition().y);
	wstring wtext(model.getText().begin(), model.getText().end());

	DrawText(buffer, wtext.c_str(), wtext.size(), &rectangle, DT_LEFT);
}
