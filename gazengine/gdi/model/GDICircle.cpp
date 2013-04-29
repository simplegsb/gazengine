#include "stdafx.h"

#include "GDICircle.h"

GDICircle::GDICircle(HDC buffer, const Vector2& position, float radius) :
	buffer(buffer), colour(), position(position), radius(radius)
{
}

GDICircle::~GDICircle()
{
}

void GDICircle::draw()
{
	HPEN pen = CreatePen(PS_SOLID, 1, colour);
	SelectObject(buffer, pen);

	Ellipse(buffer, static_cast<int>(position.x - radius), static_cast<int>(position.y - radius),
		static_cast<int>(position.x + radius), static_cast<int>(position.y + radius));

	DeleteObject(pen);
}

COLORREF GDICircle::getColour() const
{
	return colour;
}
		
const Vector2& GDICircle::getPosition() const
{
	return position;
}

Model::PrimitiveType GDICircle::getPrimitiveType() const
{
	return Model::NA;
}
		
float GDICircle::getRadius() const
{
	return radius;
}
		
void GDICircle::setColour(COLORREF colour)
{
	this->colour = colour;
}
		
void GDICircle::setPosition(const Vector2& position)
{
	this->position = position;
}
		
void GDICircle::setRadius(float radius)
{
	this->radius = radius;
}
