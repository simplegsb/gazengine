#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Model.h"
#include "../math/Vector2.h"

class Circle : public Model
{
	public:
		virtual const Vector2& getPosition() const = 0;
		
		virtual float getRadius() const = 0;
		
		virtual void setPosition(const Vector2& position) = 0;
		
		virtual void setRadius(float radius) = 0;
};

#endif /* CIRCLE_H_ */
