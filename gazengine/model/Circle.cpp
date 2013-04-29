#include "Circle.h"

Circle::Circle(const Vector2& position, float radius) :
	position(position),
	radius(radius),
	visible(true)
{
}

Circle::~Circle()
{
}

Texture* Circle::getNormalMap() const
{
	return NULL;
}

const Vector2& Circle::getPosition() const
{
	return position;
}

Model::PrimitiveType Circle::getPrimitiveType() const
{
	return Model::NA;
}

float Circle::getRadius() const
{
	return radius;
}

Texture* Circle::getTexture() const
{
	return NULL;
}

bool Circle::isVisible() const
{
	return visible;
}

void Circle::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void Circle::setNormalMap(Texture*)
{
}

void Circle::setPosition(const Vector2& position)
{
	this->position = position;
}

void Circle::setPrimitiveType(PrimitiveType)
{
}

void Circle::setRadius(float radius)
{
	this->radius = radius;
}

void Circle::setTexture(Texture*)
{
}

void Circle::setVisible(bool visible)
{
	this->visible = visible;
}
