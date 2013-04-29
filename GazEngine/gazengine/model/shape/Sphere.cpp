#include "Sphere.h"

Sphere::Sphere(const Vector2& position, float radius) :
	Shape(position),
	radius(radius)
{
}

float Sphere::getRadius() const
{
	return radius;
}

void Sphere::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void Sphere::setRadius(const float radius)
{
	this->radius = radius;
}
