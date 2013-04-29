#include "stdafx.h"

#include "GDIMesh.h"

GDIMesh::GDIMesh(HDC buffer, std::vector<Vector2> vertices, COLORREF colour) :
	buffer(buffer), colour(colour), vertices(vertices)
{
}

GDIMesh::~GDIMesh()
{
}

void GDIMesh::draw()
{
	if (vertices.empty())
	{
		return;
	}

	HPEN pen = CreatePen(PS_SOLID, 1, colour);
	SelectObject(buffer, pen);

	MoveToEx(buffer, (int) vertices.at(0).x, (int) vertices.at(0).y, NULL);

	for (unsigned int index = 1; index < vertices.size(); index++)
	{
		LineTo(buffer, (int) vertices.at(index).x, (int) vertices.at(index).y);
	}

	DeleteObject(pen);
}

Model::PrimitiveType GDIMesh::getPrimitiveType() const
{
	return Model::NA;
}
