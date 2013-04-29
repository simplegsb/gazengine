#include "GDIMesh.h"

using namespace std;

GDIMesh::GDIMesh(std::vector<Vector2> vertices, COLORREF colour) :
	colour(colour), vertices(vertices)
{
}

GDIMesh::~GDIMesh()
{
}

COLORREF GDIMesh::getColour() const
{
	return colour;
}

Model::PrimitiveType GDIMesh::getPrimitiveType() const
{
	return Model::NA;
}

const vector<Vector2>& GDIMesh::getVertices() const
{
	return vertices;
}

void GDIMesh::render(Renderer& renderer) const
{
	renderer.render(*this);
}
