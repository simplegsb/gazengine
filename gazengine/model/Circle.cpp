#include "Circle.h"

Circle::Circle(const Vector2& position, float radius) :
	position(position), radius(radius)
{
}

Circle::~Circle()
{
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

void Circle::setPosition(const Vector2& position)
{
	this->position = position;
}

void Circle::setRadius(float radius)
{
	this->radius = radius;
}
