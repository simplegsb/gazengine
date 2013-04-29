#include <gazengine/model/Line2.h>
#include <gazengine/model/shape/Circle.h>
#include <gazengine/model/Text.h>

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

void GDIRenderer::render(const Capsule& model)
{
}

void GDIRenderer::render(const Circle& model)
{
	COLORREF gdiColour = RGB(model.getColour().R() * 255, model.getColour().G() * 255, model.getColour().B() * 255);

	if (model.getPrimitiveType() == Model::LINE_LIST ||
		model.getPrimitiveType() == Model::LINE_STRIP)
	{
		HPEN pen = CreatePen(PS_SOLID, 1, gdiColour);
		SelectObject(buffer, pen);

		Ellipse(buffer,
			static_cast<int>(model.getPosition().X() - model.getRadius()),
			static_cast<int>(model.getPosition().Y() - model.getRadius()),
			static_cast<int>(model.getPosition().X() + model.getRadius()),
			static_cast<int>(model.getPosition().Y() + model.getRadius()));

		DeleteObject(pen);
	}
	else if (model.getPrimitiveType() == Model::TRIANGLE_LIST ||
		model.getPrimitiveType() == Model::TRIANGLE_STRIP)
	{
		HBRUSH brush = CreateSolidBrush(gdiColour);
		SelectObject(buffer, brush);

		Ellipse(buffer,
			static_cast<int>(model.getPosition().X() - model.getRadius()),
			static_cast<int>(model.getPosition().Y() - model.getRadius()),
			static_cast<int>(model.getPosition().X() + model.getRadius()),
			static_cast<int>(model.getPosition().Y() + model.getRadius()));

		DeleteObject(brush);
	}
}

void GDIRenderer::render(const Cylinder& model)
{
}

void GDIRenderer::render(const Line2& model)
{
	COLORREF gdiColour = RGB(model.getColour().R() * 255, model.getColour().G() * 255, model.getColour().B() * 255);
	HPEN pen = CreatePen(PS_SOLID, 1, gdiColour);
	SelectObject(buffer, pen);

	MoveToEx(buffer, (int) model.getPointA().X(), (int) model.getPointA().Y(), NULL);
	LineTo(buffer, (int) model.getPointB().X(), (int) model.getPointB().Y());

	DeleteObject(pen);	
}

void GDIRenderer::render(const Mesh& model)
{
	COLORREF gdiColour = RGB(model.getColour().R() * 255, model.getColour().G() * 255, model.getColour().B() * 255);
	const GDIMesh* gdiMesh = dynamic_cast<const GDIMesh*>(&model);

	if (gdiMesh == NULL)
	{
		return;
	}
	if (gdiMesh->getVertices().empty())
	{
		return;
	}

	if (model.getPrimitiveType() == Model::POINTS)
	{
		HBRUSH brush = CreateSolidBrush(gdiColour);

		for (unsigned int index = 0; index < gdiMesh->getVertices().size(); index++)
		{
			RECT rectangle;
			rectangle.bottom = (int) gdiMesh->getVertices()[index].Y();
			rectangle.left = (int) gdiMesh->getVertices()[index].X();
			rectangle.right = (int) gdiMesh->getVertices()[index].X() + 2;
			rectangle.top = (int) gdiMesh->getVertices()[index].Y() + 2;

			FillRect(buffer, &rectangle, brush);
		}

		DeleteObject(brush);
	}
	else if (model.getPrimitiveType() == Model::LINE_LIST)
	{
		HPEN pen = CreatePen(PS_SOLID, 1, gdiColour);
		SelectObject(buffer, pen);

		for (unsigned int index = 0; index < gdiMesh->getVertices().size(); index += 2)
		{
			MoveToEx(buffer, (int) gdiMesh->getVertices().at(index).X(), (int) gdiMesh->getVertices().at(index).Y(), NULL);
			LineTo(buffer, (int) gdiMesh->getVertices().at(index + 1).X(), (int) gdiMesh->getVertices().at(index + 1).Y());
		}

		DeleteObject(pen);
	}
	else if (model.getPrimitiveType() == Model::LINE_STRIP)
	{
		HPEN pen = CreatePen(PS_SOLID, 1, gdiColour);
		SelectObject(buffer, pen);

		MoveToEx(buffer, (int) gdiMesh->getVertices().at(0).X(), (int) gdiMesh->getVertices().at(0).Y(), NULL);

		for (unsigned int index = 1; index < gdiMesh->getVertices().size(); index++)
		{
			LineTo(buffer, (int) gdiMesh->getVertices().at(index).X(), (int) gdiMesh->getVertices().at(index).Y());
		}

		DeleteObject(pen);
	}
	else if (model.getPrimitiveType() == Model::TRIANGLE_LIST)
	{
		HBRUSH brush = CreateSolidBrush(gdiColour);
		SelectObject(buffer, brush);
		HPEN pen = CreatePen(PS_SOLID, 1, gdiColour);
		SelectObject(buffer, pen);

		POINT points[3];

		for (unsigned int index = 0; index < gdiMesh->getVertices().size(); index += 3)
		{
			points[0].x = static_cast<LONG>(gdiMesh->getVertices()[index].X());
			points[0].y = static_cast<LONG>(gdiMesh->getVertices()[index].Y());
			points[1].x = static_cast<LONG>(gdiMesh->getVertices()[index + 1].X());
			points[1].y = static_cast<LONG>(gdiMesh->getVertices()[index + 1].Y());
			points[2].x = static_cast<LONG>(gdiMesh->getVertices()[index + 2].X());
			points[2].y = static_cast<LONG>(gdiMesh->getVertices()[index + 2].Y());

			Polygon(buffer, points, 3);
		}

		DeleteObject(brush);
		DeleteObject(pen);
	}
	else if (model.getPrimitiveType() == Model::TRIANGLE_STRIP)
	{
		HBRUSH brush = CreateSolidBrush(gdiColour);
		SelectObject(buffer, brush);
		HPEN pen = CreatePen(PS_SOLID, 1, gdiColour);
		SelectObject(buffer, pen);

		POINT points[3];

		for (unsigned int index = 2; index < gdiMesh->getVertices().size(); index++)
		{
			points[0].x = static_cast<LONG>(gdiMesh->getVertices()[index - 2].X());
			points[0].y = static_cast<LONG>(gdiMesh->getVertices()[index - 2].Y());
			points[1].x = static_cast<LONG>(gdiMesh->getVertices()[index - 1].X());
			points[1].y = static_cast<LONG>(gdiMesh->getVertices()[index - 1].Y());
			points[2].x = static_cast<LONG>(gdiMesh->getVertices()[index].X());
			points[2].y = static_cast<LONG>(gdiMesh->getVertices()[index].Y());

			Polygon(buffer, points, 3);
		}

		DeleteObject(brush);
		DeleteObject(pen);
	}
}

void GDIRenderer::setBuffer(HDC buffer)
{
	this->buffer = buffer;
}

void GDIRenderer::render(const Sphere& model)
{
}

void GDIRenderer::render(const Text& model)
{
	RECT rectangle;
	rectangle.bottom = 10000; // Unlimited height
	rectangle.left = static_cast<LONG>(model.getPosition().X());
	rectangle.right = 10000; // Unlimited width
	rectangle.top = static_cast<LONG>(model.getPosition().Y());
	wstring wtext(model.getText().begin(), model.getText().end());

	DrawText(buffer, wtext.c_str(), wtext.size(), &rectangle, DT_LEFT);
}

void GDIRenderer::render(const Torus& model)
{
}
