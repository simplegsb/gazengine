#ifndef GDICIRCLE_H_
#define GDICIRCLE_H_

#include <windows.h>

#include "../../model/Circle.h"

class GDICircle : public Circle
{
	public:
		GDICircle(const Vector2& position, float radius);

		virtual ~GDICircle();

		COLORREF getColour() const;

		void setColour(COLORREF colour);

	private:
		COLORREF colour;
};

#endif /* GDICIRCLE_H_ */
