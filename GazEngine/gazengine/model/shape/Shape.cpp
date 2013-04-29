#include "Shape.h"

Shape::Shape(const Vector2& position) :
	colour(0.0f, 0.0f, 0.0f, 1.0f),
	levelOfDetail(1),
	position(position),
	visible(true)
{
}

Shape::~Shape()
{
}

const Vector4& Shape::getColour() const
{
	return colour;
}

unsigned int Shape::getLevelOfDetail() const
{
	return levelOfDetail;
}

Texture* Shape::getNormalMap() const
{
	return NULL;
}

const Vector2& Shape::getPosition() const
{
	return position;
}

Model::PrimitiveType Shape::getPrimitiveType() const
{
	return Model::NA;
}

Texture* Shape::getTexture() const
{
	return NULL;
}

bool Shape::isVisible() const
{
	return visible;
}

void Shape::setColour(const Vector4& colour)
{
	this->colour = colour;
}

void Shape::setLevelOfDetail(unsigned int levelOfDetail)
{
	this->levelOfDetail = levelOfDetail;
}

void Shape::setNormalMap(Texture*)
{
}

void Shape::setPosition(const Vector2& position)
{
	this->position = position;
}

void Shape::setPrimitiveType(PrimitiveType)
{
}

void Shape::setTexture(Texture*)
{
}

void Shape::setVisible(bool visible)
{
	this->visible = visible;
}
