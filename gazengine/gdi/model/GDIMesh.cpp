#include "GDIMesh.h"

using namespace std;

GDIMesh::GDIMesh(std::vector<Vector2> vertices, COLORREF colour) :
	colour(colour),
	primitiveType(TRIANGLE_STREAM),
	vertices(vertices),
	visible(true)
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
	return primitiveType;
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

bool GDIMesh::isVisible() const
{
	return visible;
}

void GDIMesh::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void GDIMesh::setNormalMap(Texture*)
{
}

void GDIMesh::setPrimitiveType(PrimitiveType primitiveType)
{
	this->primitiveType = primitiveType;
}

void GDIMesh::setTexture(Texture*)
{
}

void GDIMesh::setVisible(bool visible)
{
	this->visible = visible;
}
