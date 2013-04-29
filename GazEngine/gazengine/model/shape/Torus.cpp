#include "Torus.h"

Torus::Torus(const Vector2& position, float innerRadius, float outerRadius) :
	Shape(position),
	innerRadius(innerRadius),
	outerRadius(outerRadius)
{
}

float Torus::getInnerRadius() const
{
	return innerRadius;
}

float Torus::getOuterRadius() const
{
	return outerRadius;
}

void Torus::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void Torus::setInnerRadius(const float innerRadius)
{
	this->innerRadius = innerRadius;
}

void Torus::setOuterRadius(const float outerRadius)
{
	this->outerRadius = outerRadius;
}
