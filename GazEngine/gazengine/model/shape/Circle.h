#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Shape.h"

class Circle : public Shape
{
	public:
		Circle(const Vector2& position, float radius);

		float getRadius() const;

		void render(Renderer& renderer) const;

		void setRadius(float radius);

	private:
		float radius;
};

#endif /* CIRCLE_H_ */
