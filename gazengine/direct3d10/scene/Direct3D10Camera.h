#ifndef DIRECT3D10CAMERA_H_
#define DIRECT3D10CAMERA_H_

#include <d3dx10.h>

#include "../../graph/SimpleTree.h"

class Direct3D10Camera
{
	public:
		Direct3D10Camera();

		float getFarClippingDistance() const;

		D3DXMATRIX getFinalTransformation() const;

		float getFrameHeight() const;

		float getFrameWidth() const;

		float getNearClippingDistance() const;

		SimpleTree* getNode();

		D3DXVECTOR3 getTranslation() const;

		void lookAt(const D3DXVECTOR3& target, const D3DXVECTOR3& up);

		void setFarClippingDistance(float farClippingDistance);

		void setNearClippingDistance(float nearClippingDistance);

		void setNode(SimpleTree* node);

		void setOrthogonal(float width, float height);

		void setPerspective(float yAxisFieldOfView, float aspectRatio);

		void setTranslation(const D3DXVECTOR3& translation);

	private:
		float farClippingDistance;

		float frameHeight;

		float nearClippingDistance;

		SimpleTree* node;

		D3DXMATRIX projection;

		D3DXVECTOR3 translation;

		D3DXMATRIX view;

		float frameWidth;
};

#endif /* DIRECT3D10SHADER_H_ */
