#include "Line2.h"

Line2::Line2(const Vector2& pointA, const Vector2& pointB) :
	color(0.0f, 0.0f, 0.0f),
	pointA(pointA),
	pointB(pointB),
	visible(true)
{
}

const Vector3& Line2::getColor() const
{
	return color;
}

Texture* Line2::getNormalMap() const
{
	return NULL;
}

const Vector2& Line2::getPointA() const
{
	return pointA;
}

const Vector2& Line2::getPointB() const
{
	return pointB;
}

Model::PrimitiveType Line2::getPrimitiveType() const
{
	return Model::NA;
}

Texture* Line2::getTexture() const
{
	return NULL;
}

bool Line2::isVisible() const
{
	return visible;
}

void Line2::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void Line2::setColor(const Vector3& color)
{
	this->color = color;
}

void Line2::setNormalMap(Texture*)
{
}

void Line2::setPointA(const Vector2& pointA)
{
	this->pointA = pointA;
}

void Line2::setPointB(const Vector2& pointB)
{
	this->pointB = pointB;
}

void Line2::setPrimitiveType(PrimitiveType)
{
}

void Line2::setTexture(Texture*)
{
}

void Line2::setVisible(bool visible)
{
	this->visible = visible;
}
