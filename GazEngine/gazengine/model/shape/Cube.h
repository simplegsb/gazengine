#ifndef CUBE_H_
#define CUBE_H_

#include "Shape.h"

class Cube : public Shape
{
	public:
		Cube(const Vector2& position, float halfEdgeLength);

		float getHalfEdgeLength() const;

		void render(Renderer& renderer) const;

		void setHalfEdgeLength(float halfEdgeLength);

	private:
		float halfEdgeLength;
};

#endif /* CUBE_H_ */
