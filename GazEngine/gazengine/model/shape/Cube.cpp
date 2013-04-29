#include "Cube.h"

Cube::Cube(const Vector2& position, float halfEdgeLength) :
	Shape(position),
	halfEdgeLength(halfEdgeLength)
{
}

float Cube::getHalfEdgeLength() const
{
	return halfEdgeLength;
}

void Cube::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void Cube::setHalfEdgeLength(float halfEdgeLength)
{
	this->halfEdgeLength = halfEdgeLength;
}
