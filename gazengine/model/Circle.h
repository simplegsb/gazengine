#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Model.h"
#include "../math/Vector2.h"

class Circle : public Model
{
	public:
		Circle(const Vector2& position, float radius);

		virtual ~Circle();

		Texture* getNormalMap() const;

		const Vector2& getPosition() const;

		float getRadius() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		bool isVisible() const;

		void render(Renderer& renderer) const;

		void setNormalMap(Texture* texture);

		void setPosition(const Vector2& position);

		void setPrimitiveType(PrimitiveType primitiveType);

		void setRadius(float radius);

		void setTexture(Texture* texture);

		void setVisible(bool visible);

	private:
		Vector2 position;

		float radius;

		bool visible;
};

#endif /* CIRCLE_H_ */
