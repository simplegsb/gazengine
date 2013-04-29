#include "Circle.h"

Circle::Circle(const Vector2& position, float radius) :
	Shape(position),
	radius(radius)
{
}

float Circle::getRadius() const
{
	return radius;
}

void Circle::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void Circle::setRadius(float radius)
{
	this->radius = radius;
}
