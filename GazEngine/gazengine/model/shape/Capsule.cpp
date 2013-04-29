#include "Capsule.h"

Capsule::Capsule(const Vector2& position, float length, float radius) :
	Shape(position),
	length(length),
	radius(radius)
{
}

float Capsule::getLength() const
{
	return length;
}

float Capsule::getRadius() const
{
	return radius;
}

void Capsule::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void Capsule::setLength(const float length)
{
	this->length = length;
}

void Capsule::setRadius(const float radius)
{
	this->radius = radius;
}
