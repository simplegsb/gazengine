#include "GDICircle.h"

GDICircle::GDICircle(const Vector2& position, float radius) : Circle(position, radius),
	colour()
{
}

GDICircle::~GDICircle()
{
}

COLORREF GDICircle::getColour() const
{
	return colour;
}
		
void GDICircle::setColour(COLORREF colour)
{
	this->colour = colour;
}
