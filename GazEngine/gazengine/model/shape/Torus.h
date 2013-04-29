#ifndef TORUS_H_
#define TORUS_H_

#include "Shape.h"

class Torus : public Shape
{
	public:
		Torus(const Vector2& position, float innerRadius, float outerRadius);

		float getInnerRadius() const;

		float getOuterRadius() const;

		void render(Renderer& renderer) const;

		void setInnerRadius(const float innerRadius);

		void setOuterRadius(const float outerRadius);

	private:
		float innerRadius;

		float outerRadius;
};

#endif /* TORUS_H_ */
