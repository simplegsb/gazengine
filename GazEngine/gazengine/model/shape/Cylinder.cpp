#include "Cylinder.h"

Cylinder::Cylinder(const Vector2& position, float length, float radius) :
	Shape(position),
	length(length),
	radius(radius)
{
}

float Cylinder::getLength() const
{
	return length;
}

float Cylinder::getRadius() const
{
	return radius;
}

void Cylinder::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void Cylinder::setLength(const float length)
{
	this->length = length;
}

void Cylinder::setRadius(const float radius)
{
	this->radius = radius;
}
