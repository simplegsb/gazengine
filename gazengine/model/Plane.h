#ifndef PLANE_H_
#define PLANE_H_

#include "Model.h"
#include "../math/Vector3.h"

class Plane : public Model
{
	public:
		Plane(const Vector3& normal, const Vector3& positionOnPlane);

		const Vector3& getNormal() const;

		Texture* getNormalMap() const;

		const Vector3& getPositionOnPlane() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		bool isVisible() const;

		void render(Renderer& renderer) const;

		void setNormal(const Vector3& normal);

		void setNormalMap(Texture* texture);

		void setPositionOnPlane(const Vector3& positionOnPlane);

		void setTexture(Texture* texture);

		void setVisible(bool visible);

	private:
		Vector3 normal;

		Vector3 positionOnPlane;

		bool visible;
};

#endif /* PLANE_H_ */
