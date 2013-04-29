#ifndef CAMERA_H_
#define CAMERA_H_

#include "../graph/SimpleTree.h"
#include "../math/Matrix.h"
#include "../math/Vector.h"

class Camera
{
	public:
		virtual ~Camera()
		{
		}

		virtual float getFarClippingDistance() const = 0;

		virtual float getFrameHeight() const = 0;

		virtual float getFrameWidth() const = 0;

		virtual float getNearClippingDistance() const = 0;

		virtual SimpleTree* getNode() = 0;

		virtual Vector3 getTranslation() const = 0;

		virtual void lookAt(const Vector3& target, const Vector3& up) = 0;

		virtual void setFarClippingDistance(float farClippingDistance) = 0;

		virtual void setNearClippingDistance(float nearClippingDistance) = 0;

		virtual void setNode(SimpleTree* node) = 0;

		virtual void setOrthogonal(float width, float height) = 0;

		virtual void setPerspective(float yAxisFieldOfView, float aspectRatio) = 0;

		virtual void setTranslation(const Vector3& translation) = 0;
};

#endif /* CAMERA_H_ */
