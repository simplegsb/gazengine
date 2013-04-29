#include "GDIMesh.h"

using namespace std;

GDIMesh::GDIMesh(std::vector<Vector2> vertices, const Vector4& colour) :
	colour(colour),
	primitiveType(TRIANGLE_STRIP),
	vertices(vertices),
	visible(true)
{
}

GDIMesh::~GDIMesh()
{
}

const Vector4& GDIMesh::getColour() const
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

void GDIMesh::setColour(const Vector4& colour)
{
	this->colour = colour;
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
