#ifndef CAPSULE_H_
#define CAPSULE_H_

#include "Shape.h"

class Capsule : public Shape
{
	public:
		Capsule(const Vector2& position, float length, float radius);

		float getLength() const;

		float getRadius() const;

		void render(Renderer& renderer) const;

		void setLength(const float length);

		void setRadius(const float radius);

	private:
		float length;

		float radius;
};

#endif /* CAPSULE_H_ */
