#ifndef SHAPE_H_
#define SHAPE_H_

#include "../Model.h"

class Shape : public Model
{
	public:
		Shape(const Vector2& position);

		virtual ~Shape();

		const Vector4& getColour() const;

		unsigned int getLevelOfDetail() const;

		Texture* getNormalMap() const;

		const Vector2& getPosition() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		bool isVisible() const;

		void setColour(const Vector4& colour);

		void setLevelOfDetail(unsigned int levelOfDetail);

		void setNormalMap(Texture* texture);

		void setPosition(const Vector2& position);

		void setPrimitiveType(PrimitiveType primitiveType);

		void setTexture(Texture* texture);

		void setVisible(bool visible);

	private:
		Vector4 colour;

		unsigned int levelOfDetail;

		Vector2 position;

		bool visible;
};

#endif /* SHAPE_H_ */
