#include "GDICircle.h"

GDICircle::GDICircle(const Vector2& position, float radius) : Circle(position, radius),
	colour(),
	visible(true)
{
}

GDICircle::~GDICircle()
{
}

COLORREF GDICircle::getColour() const
{
	return colour;
}

Texture* GDICircle::getNormalMap() const
{
	return NULL;
}

Model::PrimitiveType GDICircle::getPrimitiveType() const
{
	return Model::NA;
}

Texture* GDICircle::getTexture() const
{
	return NULL;
}

bool GDICircle::isVisible() const
{
	return visible;
}

void GDICircle::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void GDICircle::setColour(COLORREF colour)
{
	this->colour = colour;
}

void GDICircle::setNormalMap(Texture*)
{
}

void GDICircle::setPrimitiveType(PrimitiveType)
{
}

void GDICircle::setTexture(Texture*)
{
}

void GDICircle::setVisible(bool visible)
{
	this->visible = visible;
}
