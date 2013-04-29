#include "Plane.h"

Plane::Plane(const Vector3& normal, const Vector3& positionOnPlane) :
	normal(normal),
	positionOnPlane(positionOnPlane)
{
}

const Vector3& Plane::getNormal() const
{
	return normal;
}

Texture* Plane::getNormalMap() const
{
	return NULL;
}

const Vector3& Plane::getPositionOnPlane() const
{
	return positionOnPlane;
}

Model::PrimitiveType Plane::getPrimitiveType() const
{
	return NA;
}

Texture* Plane::getTexture() const
{
	return NULL;
}

bool Plane::isVisible() const
{
	return visible;
}

void Plane::render(Renderer&) const
{
}

void Plane::setNormal(const Vector3& normal)
{
	this->normal = normal;
}

void Plane::setNormalMap(Texture*)
{
}

void Plane::setPositionOnPlane(const Vector3& positionOnPlane)
{
	this->positionOnPlane = positionOnPlane;
}

void Plane::setTexture(Texture*)
{
}

void Plane::setVisible(bool visible)
{
	this->visible = visible;
}
