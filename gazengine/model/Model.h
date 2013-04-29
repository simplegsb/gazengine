#ifndef MODEL_H_
#define MODEL_H_

#include "../rendering/Renderer.h"
#include "../rendering/Texture.h"

class Model
{
	public:
		enum PrimitiveType
		{
			LINE_LIST,
			NA,
			TRIANGLE_LIST
		};

		virtual ~Model()
		{
		}

		virtual Texture* getNormalMap() const = 0;

		virtual PrimitiveType getPrimitiveType() const = 0;

		virtual Texture* getTexture() const = 0;

		virtual void render(Renderer& renderer) const = 0;

		virtual void setNormalMap(Texture* texture) = 0;

		virtual void setTexture(Texture* texture) = 0;
};

#endif /* MODEL_H_ */
