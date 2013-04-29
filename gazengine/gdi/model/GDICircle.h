#ifndef GDICIRCLE_H_
#define GDICIRCLE_H_

#include <windows.h>

#include "../../model/Circle.h"

class GDICircle : public Circle
{
	public:
		GDICircle(const Vector2& position, float radius);

		virtual ~GDICircle();

		COLORREF getColour() const;

		Texture* getNormalMap() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		bool isVisible() const;

		void render(Renderer& renderer) const;

		void setColour(COLORREF colour);

		void setNormalMap(Texture* texture);

		void setPrimitiveType(PrimitiveType primitiveType);

		void setTexture(Texture* texture);

		void setVisible(bool visible);

	private:
		COLORREF colour;

		bool visible;
};

#endif /* GDICIRCLE_H_ */
