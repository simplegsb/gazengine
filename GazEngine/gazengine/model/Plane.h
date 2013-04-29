#ifndef PLANE_H_
#define PLANE_H_

#include "Model.h"

class Plane : public Model
{
	public:
		Plane(const Vector3& normal, const Vector3& positionOnPlane);

		const Vector4& getColour() const;

		const Vector3& getNormal() const;

		Texture* getNormalMap() const;

		const Vector3& getPositionOnPlane() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		bool isVisible() const;

		void render(Renderer& renderer) const;

		void setColour(const Vector4& colour);

		void setNormal(const Vector3& normal);

		void setNormalMap(Texture* texture);

		void setPositionOnPlane(const Vector3& positionOnPlane);

		void setPrimitiveType(PrimitiveType primitiveType);

		void setTexture(Texture* texture);

		void setVisible(bool visible);

	private:
		Vector4 colour;

		Vector3 normal;

		Vector3 positionOnPlane;

		bool visible;
};

#endif /* PLANE_H_ */
