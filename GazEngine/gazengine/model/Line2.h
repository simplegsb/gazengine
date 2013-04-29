#ifndef LINE2_H_
#define LINE2_H_

#include "Model.h"

class Line2 : public Model
{
	public:
		Line2(const Vector2& pointA, const Vector2& pointB);

		const Vector4& getColour() const;

		Texture* getNormalMap() const;

		const Vector2& getPointA() const;

		const Vector2& getPointB() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		bool isVisible() const;

		void render(Renderer& renderer) const;

		void setColour(const Vector4& color);

		void setNormalMap(Texture* texture);

		void setPointA(const Vector2& pointA);

		void setPointB(const Vector2& pointB);

		void setPrimitiveType(PrimitiveType primitiveType);

		void setTexture(Texture* texture);

		void setVisible(bool visible);

	private:
		Vector4 colour;

		Vector2 pointA;

		Vector2 pointB;

		bool visible;
};

#endif /* LINE2_H_ */
