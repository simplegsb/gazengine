#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Model.h"
#include "../math/Vector2.h"

class Circle : public Model
{
	public:
		Circle(const Vector2& position, float radius);

		virtual ~Circle();

		const Vector2& getPosition() const;
		
		float getRadius() const;

		PrimitiveType getPrimitiveType() const;
		
		void setPosition(const Vector2& position);
		
		void setRadius(float radius);

	private:
		Vector2 position;

		float radius;
};

#endif /* CIRCLE_H_ */
