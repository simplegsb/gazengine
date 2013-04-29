#ifndef DIRECT3D10CAMERA_H_
#define DIRECT3D10CAMERA_H_

#include <gazengine/graph/SimpleTree.h>
#include <gazengine/scene/Camera.h>

class Direct3D10Camera : public Camera
{
	public:
		Direct3D10Camera();

		float getFarClippingDistance() const;

		Matrix44 getFinalTransformation() const;

		float getFrameHeight() const;

		float getFrameWidth() const;

		float getNearClippingDistance() const;

		SimpleTree* getNode();

		Vector3 getTranslation() const;

		void lookAt(const Vector3& target, const Vector3& up);

		void setFarClippingDistance(float farClippingDistance);

		void setNearClippingDistance(float nearClippingDistance);

		void setNode(SimpleTree* node);

		void setOrthogonal(float width, float height);

		void setPerspective(float yAxisFieldOfView, float aspectRatio);

		void setTranslation(const Vector3& translation);

	private:
		float farClippingDistance;

		float frameHeight;

		float nearClippingDistance;

		SimpleTree* node;

		Matrix44 projection;

		Vector3 translation;

		Matrix44 view;

		float frameWidth;
};

#endif /* DIRECT3D10CAMERA_H_ */
