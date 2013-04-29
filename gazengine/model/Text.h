#ifndef TEXT_H_
#define TEXT_H_

#include "Model.h"
#include "../math/Vector2.h"

class Text : public Model
{
	public:
		Text(const Vector2& position, const std::string& text);

		Texture* getNormalMap() const;

		const Vector2& getPosition() const;

		PrimitiveType getPrimitiveType() const;

		const std::string& getText() const;

		Texture* getTexture() const;

		bool isVisible() const;

		void render(Renderer& renderer) const;

		void setNormalMap(Texture* texture);

		void setPosition(const Vector2& position);

		void setPrimitiveType(PrimitiveType primitiveType);

		void setText(const std::string& text);

		void setTexture(Texture* texture);

		void setVisible(bool visible);

	private:
		Vector2 position;

		std::string text;

		bool visible;
};

#endif /* TEXT_H_ */
