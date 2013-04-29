#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "Shape.h"

class Cylinder : public Shape
{
	public:
		Cylinder(const Vector2& position, float length, float radius);

		float getLength() const;

		float getRadius() const;

		void render(Renderer& renderer) const;

		void setLength(const float length);

		void setRadius(const float radius);

	private:
		float length;

		float radius;
};

#endif /* CYLINDER_H_ */
