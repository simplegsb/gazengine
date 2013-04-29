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

Texture* GDIMesh::getNormalMap() const
{
	return NULL;
}

Model::PrimitiveType GDIMesh::getPrimitiveType() const
{
	return Model::NA;
}

Texture* GDIMesh::getTexture() const
{
	return NULL;
}

vector<Vector2>& GDIMesh::getVertices()
{
	return vertices;
}

const vector<Vector2>& GDIMesh::getVertices() const
{
	return vertices;
}

void GDIMesh::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void GDIMesh::setNormalMap(Texture*)
{
}

void GDIMesh::setTexture(Texture*)
{
}
