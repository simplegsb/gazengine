#ifndef GDICIRCLE_H_
#define GDICIRCLE_H_

#include <windows.h>

#include "../../model/Circle.h"

class GDICircle : public Circle
{
	public:
		GDICircle(HDC buffer, const Vector2& position, float radius);

		virtual ~GDICircle();
		
		void draw();
		
		COLORREF getColour() const;
		
		const Vector2& getPosition() const;
		
		PrimitiveType getPrimitiveType() const;
		
		float getRadius() const;
		
		void setColour(COLORREF colour);
		
		void setPosition(const Vector2& position);
		
		void setRadius(float radius);

	private:
		HDC buffer;

		COLORREF colour;

		Vector2 position;

		float radius;
};

#endif /* GDICIRCLE_H_ */
