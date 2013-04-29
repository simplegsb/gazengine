#ifndef MODEL_H_
#define MODEL_H_

#include "../Component.h"
#include "../math/Vector.h"
#include "../rendering/Renderer.h"
#include "../rendering/Texture.h"

class Model : public Component
{
	public:
		struct Material
		{
			Vector4 ambient;

			Vector4 diffuse;

			Vector4 emmissive;

			float specularPower;

			Vector4 specular;
		};

		enum PrimitiveType
		{
			LINE_LIST,
			LINE_STRIP,
			NA,
			POINTS,
			TRIANGLE_LIST,
			TRIANGLE_STRIP
		};

		virtual ~Model()
		{
		}

		virtual const Vector4& getColour() const = 0;

		virtual const Material& getMaterial() const = 0;

		virtual Texture* getNormalMap() const = 0;

		virtual PrimitiveType getPrimitiveType() const = 0;

		virtual Texture* getTexture() const = 0;

		virtual bool isVisible() const = 0;

		virtual void render(Renderer& renderer) const = 0;

		virtual void setColour(const Vector4& color) = 0;

		virtual void setMaterial(const Material& material) = 0;

		virtual void setNormalMap(Texture* texture) = 0;

		virtual void setPrimitiveType(PrimitiveType primitiveType) = 0;

		virtual void setTexture(Texture* texture) = 0;

		virtual void setVisible(bool visible) = 0;
};

#endif /* MODEL_H_ */
