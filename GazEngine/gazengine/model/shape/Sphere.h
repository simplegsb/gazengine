#ifndef SPHERE_H_
#define SPHERE_H_

#include "Shape.h"

class Sphere : public Shape
{
	public:
		Sphere(const Vector2& position, float radius);

		float getRadius() const;

		void render(Renderer& renderer) const;

		void setRadius(const float radius);

	private:
		float radius;
};

#endif /* SPHERE_H_ */
